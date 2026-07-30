#include "Patron.h"
#include <iostream> // Needed for cout, endl, ostream
#include <stdexcept> // Needed for runtime_error
using namespace std;

Patron::Patron(string n, int i) : name(n), id(i) {}

void Patron::borrowBook(Book* b) {
    if (b && b->getStatus() == BookStatus::Available) {
        borrowedBooks.push_back(b);
        b->setStatus(BookStatus::CheckedOut);
    } 
    else {
        throw runtime_error("Book is not available or invalid.");
    }
}

void Patron::returnBook(Book* b) {
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
        if (*it == b) {
            borrowedBooks.erase(it); 
            b->setStatus(BookStatus::Available);
            return;
        }
    }
    throw runtime_error("Book not found in borrowed list.");
}


void Patron::displayPatron() const {
    cout << "Patron Name: " << name << ", ID: " << id << endl;
    cout << "Borrowed Books: " << endl;
    for (const auto& book : borrowedBooks) {
        book->displayInfo();
        cout << endl;
    }
}

bool Patron::operator==(const Patron& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& os, const Patron& p) {
    os << "Patron Name: " << p.name << ", ID: " << p.id;
    return os;
}   