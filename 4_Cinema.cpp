// Cinema.cpp
// the whole theatre. basically just a name and a bunch of screens.
#ifndef CINEMA_CPP
#define CINEMA_CPP

#include <string>
#include <vector>
#include "3_Screen.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema(string name) {
        this->name = name;
    }

    void addScreen(Screen screen) {
        screens.push_back(screen);
    }

    string getName() { return name; }
    vector<Screen>& getScreens() { return screens; }
};

#endif
