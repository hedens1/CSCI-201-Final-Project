#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <fstream>
#include "Book.h"
#include "Patron.h"
#include "Transaction.h"



class Library {
    std::vector<Book*> books;
    std::vector<Patron*> patrons;
    std::vector<Transaction> transactions;

public:
    ~Library();
    
    void loadData();
    void saveData();

    void addBook(Book* b);
    void addPatron(Patron* p); 
    void borrowBook(int patronId, const std::string& bookTitle);
    void returnBook(int patronId, const std::string& bookTitle);

    void displayBooks() const;
    void displayPatrons() const;
    void displayTransactions() const;

    // Search functions
    Book* findBookByTitle(const std::string& title) const;
    Patron* findPatronById(int id) const;
    std::vector<Book*> searchByGenre(Genre genre) const;
    std::vector<Book> searchByAuthor(const std::string& author) const;
    
    template<typename T>
    void saveToFile(const std::vector<T>& items, const std::string& filename) const;
};

// Template Implementation (Must be in header)
template<typename T>
void Library::saveToFile(const std::vector<T>& items, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    // Implementation details...
    file.close();
}

#endif // LIBRARY_H   