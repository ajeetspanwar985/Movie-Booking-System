// Show.cpp
// a Show is basically "this movie is playing on this screen at this time".
// it builds its own list of ShowSeats when created (one for every seat on
// the screen it's using).
#ifndef SHOW_CPP
#define SHOW_CPP

#include <string>
#include <vector>
#include <iostream>
#include "1_Movie.cpp"
#include "3_Screen.cpp"
#include "6_ShowSeat.cpp"
using namespace std;

class Show {
private:
    string showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show() {
        movie = NULL;
        screen = NULL;
    }

    Show(string showId, Movie* movie, Screen* screen, string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        // make a ShowSeat for every seat on this screen
        vector<Seat> screenSeats = screen->getSeats();
        for (int i = 0; i < (int)screenSeats.size(); i++) {
            showSeats.push_back(ShowSeat(screenSeats[i]));
        }
    }

    string getShowId() { return showId; }
    Movie* getMovie() { return movie; }
    Screen* getScreen() { return screen; }
    string getStartTime() { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    // looks for a seat by its number, e.g. "A1". returns NULL if not found
    // so the caller can print an error instead of crashing.
    ShowSeat* findShowSeat(string seatNumber) {
        for (int i = 0; i < (int)showSeats.size(); i++) {
            if (showSeats[i].getSeat().getSeatNumber() == seatNumber) {
                return &showSeats[i];
            }
        }
        return NULL;
    }

    void printSeatLayout() {
        cout << endl << "  " << screen->getScreenName() << "  " << startTime
             << "  |  " << movie->getTitle() << endl;

        SeatType order[3] = { SeatType::SILVER, SeatType::GOLD, SeatType::PLATINUM };
        for (int t = 0; t < 3; t++) {
            cout << "  " << Seat::typeToString(order[t]) << "\t";
            for (int i = 0; i < (int)showSeats.size(); i++) {
                if (showSeats[i].getSeat().getType() == order[t]) {
                    string mark = showSeats[i].isAvailable() ? "[ ]" : "[X]";
                    cout << showSeats[i].getSeat().getSeatNumber() << mark << " ";
                }
            }
            cout << endl;
        }
        cout << "  ( [ ] = available   [X] = booked )" << endl;
    }
};

#endif
