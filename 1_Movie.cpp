// Movie.cpp
// just holds the basic info about a movie. title, language, duration.
// nothing fancy here, this class doesn't need to know about anything else.
#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int durationMinutes;

public:
    // default constructor, just in case we need an empty movie somewhere
    Movie() {
        title = "Untitled";
        language = "Unknown";
        durationMinutes = 0;
    }

    Movie(string title, string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    string getTitle() { return title; }
    string getLanguage() { return language; }
    int getDurationMinutes() { return durationMinutes; }
};

#endif
