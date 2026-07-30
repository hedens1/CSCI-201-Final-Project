#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <vector>
#include "Book.h"

//for the people who use the library
class Patron {
    std::string name;
    int id;
    std::vector<Book*> borrowedBooks;
public:
    Patron(std::string n, int i);

    void borrowBook(Book* b);
    void returnBook(Book* b);
    void displayPatron() const; 

    std::string getName() const { return name; }
    int getId() const { return id; }
    const std::vector<Book*>& getBorrowedBooks() const { return borrowedBooks; }

    bool operator==(const Patron& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Patron& p);
};

#endif // PATRON_H   