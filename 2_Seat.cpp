// Seat.cpp
// one physical seat in a screen. has a number like "A1" and a type.
// this does NOT store whether it's booked or not - that changes per show,
// so that goes in ShowSeat instead (took me a while to realize this lol)
#ifndef SEAT_CPP
#define SEAT_CPP

#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    Seat() {
        seatNumber = "";
        type = SeatType::SILVER;
    }

    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    string getSeatNumber() { return seatNumber; }
    SeatType getType() { return type; }

    // just converts the enum to text so we can print it
    static string typeToString(SeatType t) {
        if (t == SeatType::SILVER) return "SILVER";
        if (t == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};

#endif
