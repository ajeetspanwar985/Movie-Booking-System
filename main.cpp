// main.cpp
// this is just the console menu, doesn't have any real logic in it,
// just reads input and calls the right functions.
//
// quick note: our teacher said "no header files" but also "one class per
// file", so I just made every class its own .cpp file with an include
// guard and #include them where needed (mainly here in main.cpp). it's
// not exactly how real projects separate .h and .cpp but it follows both
// rules given in the assignment.
#include <iostream>
#include <string>
#include <vector>
#include "4_Cinema.cpp"
#include "5_Show.cpp"
#include "7_Customer.cpp"
#include "10_PaymentTypes.cpp"
#include "13_BookingService.cpp"
using namespace std;

// splits something like "A1,B2" into {"A1", "B2"}
// doing this manually with find() instead of stringstream, keeps it simple
vector<string> splitSeats(string input) {
    vector<string> seats;
    string current = "";
    for (int i = 0; i < (int)input.length(); i++) {
        char c = input[i];
        if (c == ',') {
            if (current.length() > 0) seats.push_back(current);
            current = "";
        } else if (c != ' ') {
            current += c;
        }
    }
    if (current.length() > 0) seats.push_back(current);
    return seats;
}

int main() {
    // just some sample data so we have something to book. in a real system
    // this would come from a database instead of being typed in here.
    Cinema cinema("PVR Downtown");

    Movie m1("3 Idiots", "Hindi", 170);
    Movie m2("Interstellar", "English", 169);

    Screen screen1("Screen-1");
    Screen screen2("Screen-2");
    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Show show1("S1", &m1, &cinema.getScreens()[0], "06:00 PM");
    Show show2("S2", &m1, &cinema.getScreens()[1], "09:00 PM");

    BookingService bookingService;
    Customer currentCustomer("Guest", "9999999999");

    cout << "===== MOVIE TICKET BOOKING =====" << endl;

    bool running = true;
    while (running) {
        cout << endl << "1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit" << endl;
        cout << "Choose: ";
        int choice;
        cin >> choice;

        if (cin.fail()) {
            // user typed something that's not a number
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        if (choice == 1) {
            cout << endl;
            cout << "  [1] " << m1.getTitle() << "\t" << m1.getLanguage() << "\t" << m1.getDurationMinutes() << " min" << endl;
            cout << "  [2] " << m2.getTitle() << "\t" << m2.getLanguage() << "\t" << m2.getDurationMinutes() << " min" << endl;

        } else if (choice == 2) {
            cout << endl << "Choose movie: ";
            int mChoice;
            cin >> mChoice;
            if (mChoice != 1) {
                cout << "  Only 3 Idiots has shows set up in this demo, sorry." << endl;
                continue;
            }

            cout << "  [1] " << show1.getScreen()->getScreenName() << "  " << show1.getStartTime() << endl;
            cout << "  [2] " << show2.getScreen()->getScreenName() << "  " << show2.getStartTime() << endl;
            cout << "Choose show: ";
            int sChoice;
            cin >> sChoice;

            Show* chosenShow;
            if (sChoice == 1) chosenShow = &show1;
            else if (sChoice == 2) chosenShow = &show2;
            else {
                cout << "  Invalid show choice." << endl;
                continue;
            }

            chosenShow->printSeatLayout();

            cout << endl << "Seats (e.g. A1,B2): ";
            cin.ignore();
            string seatLine;
            getline(cin, seatLine);
            vector<string> seatNumbers = splitSeats(seatLine);

            if (seatNumbers.size() == 0) {
                cout << "  You didn't enter any seats." << endl;
                continue;
            }

            // show the price breakdown before asking for payment
            double preview = 0;
            bool allValid = true;
            for (int i = 0; i < (int)seatNumbers.size(); i++) {
                ShowSeat* ss = chosenShow->findShowSeat(seatNumbers[i]);
                if (ss == NULL) {
                    allValid = false;
                    break;
                }
                int price = PriceCalculator::priceOf(ss->getSeat().getType());
                cout << "  " << seatNumbers[i] << " " << Seat::typeToString(ss->getSeat().getType()) << " Rs." << price << endl;
                preview += price;
            }
            if (!allValid) {
                cout << "  One of those seat numbers doesn't exist." << endl;
                continue;
            }
            cout << "  TOTAL\t\tRs." << preview << endl;

            cout << endl << "Pay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice;
            cin >> payChoice;

            Payment* payment;
            if (payChoice == 1) payment = new UpiPayment();
            else if (payChoice == 2) payment = new CardPayment();
            else if (payChoice == 3) payment = new CashPayment();
            else {
                cout << "  Invalid payment choice." << endl;
                continue;
            }

            bookingService.bookAndPay(chosenShow, currentCustomer, seatNumbers, *payment);
            delete payment;

        } else if (choice == 3) {
            cout << endl << "Enter booking id to cancel: ";
            string bookingId;
            cin >> bookingId;
            bookingService.cancelBooking(bookingId);

        } else if (choice == 4) {
            vector<Booking*> mine = bookingService.myTickets(currentCustomer.getPhone());
            if (mine.size() == 0) {
                cout << "  No tickets yet." << endl;
                continue;
            }
            for (int i = 0; i < (int)mine.size(); i++) {
                cout << "  " << mine[i]->getBookingId() << " - " << mine[i]->getShow()->getMovie()->getTitle()
                     << " - " << Booking::statusToString(mine[i]->getStatus()) << endl;
            }

        } else if (choice == 0) {
            running = false;

        } else {
            cout << "  Invalid menu choice, try again." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
