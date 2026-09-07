// PaymentTypes.cpp
// the actual payment methods. all three inherit from Payment and just do
// their own thing when pay() is called.
// added a "failThisPayment" flag so we can test the failed-payment case
// without needing real bank integration lol
#ifndef PAYMENTTYPES_CPP
#define PAYMENTTYPES_CPP

#include <iostream>
#include "9_Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    bool failThisPayment;

public:
    UpiPayment() { failThisPayment = false; }
    UpiPayment(bool failThisPayment) { this->failThisPayment = failThisPayment; }

    bool pay(double amount) {
        if (failThisPayment || amount <= 0) {
            cout << "  [UPI] payment declined." << endl;
            return false;
        }
        cout << "  [UPI] Rs." << amount << " paid successfully" << endl;
        return true;
    }

    string methodName() { return "UPI"; }
};

class CardPayment : public Payment {
private:
    bool failThisPayment;

public:
    CardPayment() { failThisPayment = false; }
    CardPayment(bool failThisPayment) { this->failThisPayment = failThisPayment; }

    bool pay(double amount) {
        if (failThisPayment || amount <= 0) {
            cout << "  [CARD] transaction declined." << endl;
            return false;
        }
        cout << "  [CARD] Rs." << amount << " paid successfully" << endl;
        return true;
    }

    string methodName() { return "CARD"; }
};

class CashPayment : public Payment {
private:
    bool failThisPayment;

public:
    CashPayment() { failThisPayment = false; }
    CashPayment(bool failThisPayment) { this->failThisPayment = failThisPayment; }

    bool pay(double amount) {
        if (failThisPayment || amount <= 0) {
            cout << "  [CASH] amount not given." << endl;
            return false;
        }
        cout << "  [CASH] Rs." << amount << " received" << endl;
        return true;
    }

    string methodName() { return "CASH"; }
};

#endif
