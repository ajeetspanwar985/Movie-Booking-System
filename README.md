# Movie Ticket Booking System

A menu-driven **Movie Ticket Booking System** developed in C++ as part of the **TCS-504 System Design** assignment.

The system simulates a small movie ticket booking system for a single cinema, allowing customers to view movies and shows, check seat availability, book seats, make payments, print tickets, and cancel bookings.

---

## 📌 Project Information

- **Course:** B.Tech CSE
- **Semester:** 5th
- **Subject:** System Design
- **Subject Code:** TCS-504
- **Language:** C++
- **Application Type:** Console-based
- **Architecture:** Object-Oriented Design

---

## 🎯 Objectives

The main objectives of this project are:

- Apply Object-Oriented Programming concepts in a practical system.
- Design a modular and maintainable software system.
- Implement different relationships between classes.
- Demonstrate SOLID principles.
- Handle booking, payment, and cancellation workflows.
- Validate invalid inputs and booking conditions.

---

## ✨ Features

The system provides the following features:

### 1. List Movies
Displays all movies currently playing in the cinema.

### 2. View Shows
Allows the user to select a movie and view its available shows, including:

- Screen number
- Show start time

### 3. View Seat Layout
Displays the seat layout for a selected show with:

- Seat number
- Seat type
- Availability status

Seat status can be:

- `AVAILABLE`
- `BOOKED`

### 4. Book Seats
Customers can select one or more seats for a show.

The system rejects the complete booking if any selected seat is already booked.

### 5. Seat-Based Pricing

| Seat Type | Price |
|-----------|-------|
| SILVER | ₹150 |
| GOLD | ₹250 |
| PLATINUM | ₹400 |

The total booking amount is calculated according to the selected seats.

### 6. Payment

The system supports three payment methods:

- UPI
- Card
- Cash

A booking is confirmed only when payment succeeds.

If payment fails:

- Booking is not confirmed.
- Selected seats are released.
- Booking is marked as `FAILED`.

### 7. Ticket Printing

After successful payment, the system prints a ticket containing:

- Booking ID
- Movie
- Screen
- Show time
- Seat numbers
- Total amount
- Booking status

### 8. Cancel Booking

A customer can cancel a confirmed booking using its booking ID.

After cancellation:

- Booking status becomes `CANCELLED`.
- Previously booked seats become `AVAILABLE`.

---

## 🏗️ Class Structure

The project is divided into entity and service classes.

### Entity Classes

- `Movie`
- `Seat`
- `Screen`
- `Cinema`
- `Show`
- `ShowSeat`
- `Customer`
- `Booking`

### Payment Classes

- `Payment` - Abstract base class
- `UpiPayment`
- `CardPayment`
- `CashPayment`

### Service Classes

- `PriceCalculator`
- `TicketPrinter`
- `BookingService`

---

## 🔄 Booking Flow

```text
Customer
    |
    v
Select Movie
    |
    v
Select Show
    |
    v
View Seat Layout
    |
    v
Select Seats
    |
    v
Validate Seats
    |
    v
Calculate Price
    |
    v
Create Booking
    |
    v
Select Payment Method
    |
    v
Process Payment
   / \
  /   \
Fail   Success
 |       |
 v       v
Release  Confirm
Seats    Booking
 |       |
 v       v
FAILED   Print Ticket
Booking
🧩 OOP Concepts Used
Encapsulation

Important data members such as seat status and booking information are kept private and modified through controlled methods.

Example:

private:
    string status;

public:
    bool bookSeat();
    void releaseSeat();
Abstraction

Payment is an abstract class containing the common payment contract:

class Payment {
public:
    virtual bool pay(double amount) = 0;
};
Inheritance

The concrete payment classes inherit from the abstract Payment class.

             Payment
                ▲
        ┌───────┼────────┐
        │       │        │
       UPI     Card     Cash
Runtime Polymorphism

A Payment* can refer to different payment implementations.

Payment* payment;

payment = new UpiPayment();
payment->pay(amount);

The appropriate pay() implementation is selected at runtime.

Compile-Time Polymorphism

Overloaded constructors/methods are used where appropriate to demonstrate compile-time polymorphism.

Static Members

A static booking ID counter is used to generate unique booking IDs.

static int nextBookingId;
this Keyword

The this keyword is used inside constructors and member functions to refer to the current object.

🔗 Class Relationships

The project demonstrates different UML relationships.

Composition
Cinema ◆── Screen
Screen ◆── Seat
Show   ◆── ShowSeat

The child objects depend on the lifetime of their owning objects.

Aggregation
Show    ◇── Movie
Booking ◇── ShowSeat

The referenced objects can exist independently.

Association
Booking ──> Customer
Booking ──> Payment
BookingService ──> Booking

These classes interact without strong ownership dependency.
Inheritance
Payment
   △
   |
   ├── UpiPayment
   ├── CardPayment
   └── CashPayment
🧱 SOLID Principles
Single Responsibility Principle (SRP)

Each class has one primary responsibility.

Examples:

PriceCalculator → calculates prices
TicketPrinter → prints tickets
Booking → maintains booking information
Payment → defines payment contract
Open/Closed Principle (OCP)

The payment system can be extended with a new payment method without modifying the existing booking logic.
For example:

class NetBankingPayment : public Payment {
public:
    bool pay(double amount) override;
};
Liskov Substitution Principle (LSP)

Every payment implementation can be used wherever a Payment object is expected.

Payment* payment = new UpiPayment();

The same interface can also be used with:

Payment* payment = new CardPayment();
Payment* payment = new CashPayment();
Dependency Inversion Principle (DIP)

BookingService depends on the abstract Payment interface rather than directly depending on UpiPayment, CardPayment, or CashPayment.

BookingService(..., Payment* payment);

This allows payment implementations to be changed or extended without changing the booking flow.

⚠️ Edge Cases Handled

The system handles the following cases:

Already booked seat
Booking is rejected.
No seat status is changed.
Failed payment
Booking is not confirmed.
Selected seats are released.
Booking status becomes FAILED.
Booking cancellation
Booking status becomes CANCELLED.
Seats become AVAILABLE.
Invalid input
Invalid menu choices and seat numbers produce clear error messages.
The program does not crash.
📂 Project Structure
MovieTicketBookingSystem/
│
├── Movie.cpp
├── Seat.cpp
├── Screen.cpp
├── Cinema.cpp
├── Show.cpp
├── ShowSeat.cpp
├── Customer.cpp
├── Booking.cpp
│
├── Payment.cpp
├── UpiPayment.cpp
├── CardPayment.cpp
├── CashPayment.cpp
│
├── PriceCalculator.cpp
├── TicketPrinter.cpp
├── BookingService.cpp
│
├── main.cpp
│
└── README.md

Note: The exact file organization may be adjusted according to the final implementation.

▶️ How to Run
Using g++

Compile all .cpp files:

g++ *.cpp -o MovieTicketBooking

Run the program:

Windows
MovieTicketBooking.exe
Linux / macOS
./MovieTicketBooking
🖥️ Sample Menu
========== MOVIE TICKET BOOKING ==========

1. List Movies
2. View Shows
3. View Seat Layout
4. Book Ticket
5. Print Ticket
6. Cancel Booking
7. Exit

Enter your choice:
🎫 Sample Ticket
========================================
              TICKET
========================================

Booking ID : BK1001
Movie      : Interstellar
Screen     : Screen 1
Time       : 06:00 PM
Seats      : A1, A2
Amount     : ₹300
Status     : CONFIRMED

========================================
🛠️ Technologies Used
Language: C++
Paradigm: Object-Oriented Programming
Compiler: g++ / GCC
Interface: Console / CLI
Design: UML-based Object-Oriented Design
📚 Academic Concepts Demonstrated

This project demonstrates:

Classes and Objects
Encapsulation
Abstraction
Inheritance
Runtime Polymorphism
Compile-Time Polymorphism
Static Members
Composition
Aggregation
Association
SOLID Principles
Modular Design
Input Validation
Separation of Responsibilities
