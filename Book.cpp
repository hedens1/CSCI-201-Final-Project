#include "Book.h"
#include <iostream>
#include <string>

using namespace std;

// Book Implementation
Book::Book(string t, string a, Genre g) 
    : title(t), author(a), genre(g), status(BookStatus::Available) {}

void Book::displayInfo() const {
    cout << "Title: " << title << ", Author: " << author 
         << ", Status: " << (status == BookStatus::Available ? "Available" : "Checked Out");
}
//for the status of the book, whether or not it's available
void Book::setStatus(BookStatus s) { 
    status = s; 
}

BookStatus Book::getStatus() const { 
    return status; 
}

bool Book::operator==(const Book& other) const {
    return title == other.title && author == other.author;
}

ostream& operator<<(ostream& os, const Book& b) {
    os << "\"" << b.title << "\" by " << b.author;
    return os;
}

// EBook Implementation
EBook::EBook(string t, string a, Genre g, double size) 
    : Book(t, a, g), fileSizeMB(size) {}

void EBook::displayInfo() const {
    Book::displayInfo();
    cout << ", Type: EBook, Size: " << fileSizeMB << " MB";
}

// PrintedBook Implementation
PrintedBook::PrintedBook(string t, string a, Genre g, int pages) 
    : Book(t, a, g), pageCount(pages) {}

void PrintedBook::displayInfo() const {
    Book::displayInfo();
    cout << ", Type: Printed, Pages: " << pageCount;
}   