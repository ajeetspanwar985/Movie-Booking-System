// Payment.cpp
// abstract base class for payment methods. doesn't do anything on its own,
// just says every payment method HAS to have a pay() function.
// this is the "abstraction" part of OOP the teacher keeps talking about.
#ifndef PAYMENT_CPP
#define PAYMENT_CPP

#include <string>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;   // pure virtual, no body here
    virtual string methodName() = 0;
    virtual ~Payment() {}                  // needed since we have virtual functions
};

#endif
