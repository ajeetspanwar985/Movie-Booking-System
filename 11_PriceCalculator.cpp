// PriceCalculator.cpp
// works out how much a seat / a bunch of seats cost.
// prices are fixed constants here instead of just typing 150 everywhere
// in the code (teacher said no magic numbers).
#ifndef PRICECALCULATOR_CPP
#define PRICECALCULATOR_CPP

#include <vector>
#include "6_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
private:
    static const int SILVER_PRICE = 150;
    static const int GOLD_PRICE = 250;
    static const int PLATINUM_PRICE = 400;

public:
    static int priceOf(SeatType type) {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    // total for just one seat
    int calculateTotal(ShowSeat seat) {
        return priceOf(seat.getSeat().getType());
    }

    // total for a bunch of seats (overloaded version of the above)
    int calculateTotal(vector<ShowSeat*> seats) {
        int total = 0;
        for (int i = 0; i < (int)seats.size(); i++) {
            total += priceOf(seats[i]->getSeat().getType());
        }
        return total;
    }
};

#endif
