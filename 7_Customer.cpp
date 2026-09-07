// Customer.cpp
// just name and phone number, that's all we need to know about a customer
// for this assignment.
#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    Customer() {
        name = "Guest";
        phone = "";
    }

    Customer(string name, string phone) {
        this->name = name;
        this->phone = phone;
    }

    string getName() { return name; }
    string getPhone() { return phone; }
};

#endif
