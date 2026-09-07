// BookingService.cpp
// this is the class that actually runs the whole booking process -
// check seats, book them, calculate price, take payment, print ticket.
// also handles cancelling.
//
// important bit: this only ever talks to Payment (the abstract class), never
// to UpiPayment/CardPayment/CashPayment directly. that way if we add
// NetBankingPayment later we don't have to touch this file at all.
#ifndef BOOKINGSERVICE_CPP
#define BOOKINGSERVICE_CPP

#include <vector>
#include <string>
#include <iostream>
#include "5_Show.cpp"
#include "7_Customer.cpp"
#include "8_Booking.cpp"
#include "9_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    vector<Booking*> allBookings;   // just keeping every booking in a list, nothing fancy

public:
    // books the given seats for the show, takes payment, and prints the ticket
    // if everything goes fine. returns the Booking either way so caller can
    // check the status.
    Booking* bookAndPay(Show* show, Customer customer, vector<string> seatNumbers, Payment& payment) {
        vector<ShowSeat*> chosenSeats;

        // check ALL seats first before booking any of them - if even one is
        // bad we don't want to book the others halfway through
        for (int i = 0; i < (int)seatNumbers.size(); i++) {
            ShowSeat* ss = show->findShowSeat(seatNumbers[i]);
            if (ss == NULL) {
                cout << "  Invalid seat number: " << seatNumbers[i] << ". Booking cancelled, nothing changed." << endl;
                return NULL;
            }
            if (!ss->isAvailable()) {
                cout << "  Seat " << seatNumbers[i] << " is already BOOKED. Booking cancelled, nothing changed." << endl;
                return NULL;
            }
            chosenSeats.push_back(ss);
        }

        // ok all good, now actually book them
        for (int i = 0; i < (int)chosenSeats.size(); i++) {
            chosenSeats[i]->bookSeat();
        }

        double total = priceCalculator.calculateTotal(chosenSeats);

        Booking* booking = new Booking(show, customer, chosenSeats, total);
        allBookings.push_back(booking);

        bool paid = payment.pay(total);

        if (!paid) {
            // payment failed, so undo the seat booking and mark it failed
            for (int i = 0; i < (int)chosenSeats.size(); i++) {
                chosenSeats[i]->releaseSeat();
            }
            booking->markFailed();
            cout << "  Payment failed. Booking " << booking->getBookingId() << " NOT confirmed, seats released." << endl;
            return booking;
        }

        booking->markConfirmed();
        ticketPrinter.printTicket(*booking);
        return booking;
    }

    // cancels a booking if it exists and is currently confirmed
    bool cancelBooking(string bookingId) {
        for (int i = 0; i < (int)allBookings.size(); i++) {
            if (allBookings[i]->getBookingId() == bookingId) {
                if (allBookings[i]->getStatus() != BookingStatus::CONFIRMED) {
                    cout << "  Booking " << bookingId << " is not CONFIRMED, can't cancel it." << endl;
                    return false;
                }
                vector<ShowSeat*> seats = allBookings[i]->getBookedSeats();
                for (int j = 0; j < (int)seats.size(); j++) {
                    seats[j]->releaseSeat();
                }
                allBookings[i]->markCancelled();
                cout << "  Booking " << bookingId << " cancelled. Seats are AVAILABLE again." << endl;
                return true;
            }
        }
        cout << "  No booking found with id " << bookingId << endl;
        return false;
    }

    vector<Booking*> myTickets(string phone) {
        vector<Booking*> result;
        for (int i = 0; i < (int)allBookings.size(); i++) {
            if (allBookings[i]->getCustomer().getPhone() == phone) {
                result.push_back(allBookings[i]);
            }
        }
        return result;
    }

    ~BookingService() {
        for (int i = 0; i < (int)allBookings.size(); i++) {
            delete allBookings[i];
        }
    }
};

#endif
