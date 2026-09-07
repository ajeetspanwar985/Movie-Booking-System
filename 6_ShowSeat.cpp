// ShowSeat.cpp
// this is basically "is this seat free for THIS particular show".
// same seat A1 can be booked for the 6pm show but free for the 9pm show,
// so the booked/available status can't live inside Seat itself, it has to
// live here, one ShowSeat per seat per show.
#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP

#include "2_Seat.cpp"

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat() {
        status = SeatStatus::AVAILABLE;
    }

    ShowSeat(Seat seat) {
        this->seat = seat;
        status = SeatStatus::AVAILABLE;
    }

    Seat getSeat() { return seat; }
    SeatStatus getStatus() { return status; }

    bool isAvailable() {
        return status == SeatStatus::AVAILABLE;
    }

    // returns false if it was already booked, so caller knows it failed
    bool bookSeat() {
        if (status == SeatStatus::BOOKED) {
            return false;
        }
        status = SeatStatus::BOOKED;
        return true;
    }

    void releaseSeat() {
        status = SeatStatus::AVAILABLE;
    }
};

#endif
