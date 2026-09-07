// TicketPrinter.cpp
// only job is printing the ticket once a booking is confirmed.
// doesn't touch booking status or seats, purely just prints stuff.
#ifndef TICKETPRINTER_CPP
#define TICKETPRINTER_CPP

#include <iostream>
#include "8_Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking booking) {
        cout << endl << "  ================ TICKET ================" << endl;
        cout << "   Booking ID : " << booking.getBookingId() << endl;
        cout << "   Movie      : " << booking.getShow()->getMovie()->getTitle() << endl;
        cout << "   Screen     : " << booking.getShow()->getScreen()->getScreenName()
             << "   " << booking.getShow()->getStartTime() << endl;

        cout << "   Seats      : ";
        vector<ShowSeat*> seats = booking.getBookedSeats();
        for (int i = 0; i < (int)seats.size(); i++) {
            cout << seats[i]->getSeat().getSeatNumber();
            if (i != (int)seats.size() - 1) cout << ", ";
        }
        cout << endl;

        cout << "   Amount     : Rs." << booking.getTotalAmount()
             << "\t\tStatus: " << Booking::statusToString(booking.getStatus()) << endl;
        cout << "  =========================================" << endl;
    }
};

#endif
