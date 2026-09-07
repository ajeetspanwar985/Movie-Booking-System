// Booking.cpp
// this just stores the info for one booking - which show, which seats,
// how much it cost, and whether it's confirmed/failed/cancelled.
// it does NOT print tickets or handle payment itself, that's someone else's job.
#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <string>
#include <vector>
#include "5_Show.cpp"
#include "6_ShowSeat.cpp"
#include "7_Customer.cpp"
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

class Booking {
private:
    string bookingId;
    Show* show;
    Customer customer;
    vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;

    static int bookingCounter;   // shared by all bookings, used to make unique ids

public:
    Booking(Show* show, Customer customer, vector<ShowSeat*> seats, double totalAmount) {
        this->show = show;
        this->customer = customer;
        this->bookedSeats = seats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;

        bookingCounter++;
        bookingId = "BK" + to_string(1000 + bookingCounter);
    }

    string getBookingId() { return bookingId; }
    Show* getShow() { return show; }
    Customer getCustomer() { return customer; }
    vector<ShowSeat*> getBookedSeats() { return bookedSeats; }
    double getTotalAmount() { return totalAmount; }
    BookingStatus getStatus() { return status; }

    void markConfirmed() { status = BookingStatus::CONFIRMED; }
    void markFailed() { status = BookingStatus::FAILED; }
    void markCancelled() { status = BookingStatus::CANCELLED; }

    static string statusToString(BookingStatus s) {
        if (s == BookingStatus::PENDING) return "PENDING";
        if (s == BookingStatus::CONFIRMED) return "CONFIRMED";
        if (s == BookingStatus::FAILED) return "FAILED";
        return "CANCELLED";
    }
};

// static members need to be defined outside the class once
int Booking::bookingCounter = 0;

#endif
