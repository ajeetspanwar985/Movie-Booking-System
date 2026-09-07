// Screen.cpp
// one screen/auditorium in the cinema. it owns a bunch of seats.
// I'm just hardcoding a small layout here (4 silver, 3 gold, 2 platinum)
// since the assignment doesn't need a huge cinema, just something to demo with.
#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <string>
#include <vector>
#include "2_Seat.cpp"
using namespace std;

class Screen {
private:
    string screenName;
    vector<Seat> seats;

public:
    Screen() {
        screenName = "";
    }

    Screen(string screenName) {
        this->screenName = screenName;
        setupSeats();
    }

    void setupSeats() {
        // Row A = Silver
        for (int i = 1; i <= 4; i++) {
            string num = "A" + to_string(i);
            seats.push_back(Seat(num, SeatType::SILVER));
        }
        // Row B = Gold
        for (int i = 1; i <= 3; i++) {
            string num = "B" + to_string(i);
            seats.push_back(Seat(num, SeatType::GOLD));
        }
        // Row C = Platinum
        for (int i = 1; i <= 2; i++) {
            string num = "C" + to_string(i);
            seats.push_back(Seat(num, SeatType::PLATINUM));
        }
    }

    string getScreenName() { return screenName; }
    vector<Seat> getSeats() { return seats; }
};

#endif
