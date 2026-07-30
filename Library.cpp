#include "Library.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

Library::~Library() {
    for (Book* b : books) {
        delete b;
    }
}

void Library::addBook(Book* b) {
    books.push_back(b);
}

void Library::addPatron(Patron* p) { 
    patrons.push_back(p);
}

void Library::loadData() {
    // Load books
    ifstream bookFile("books.txt");
    if (!bookFile) {
        throw runtime_error("Could not open or find books.txt");
    }

    string line;
    while (getline(bookFile, line)) {
        istringstream iss(line);
        string genreStr, title, author, type;

        getline(iss, title, ',');
        getline(iss, author, ',');
        getline(iss, genreStr, ',');
        getline(iss, type, ',');

        Genre genre;
        if (genreStr == "Fiction") genre = Genre::Fiction;
        else if (genreStr == "NonFiction") genre = Genre::NonFiction;
        else if (genreStr == "Mystery") genre = Genre::Mystery;
        else if (genreStr == "ScienceFiction") genre = Genre::ScienceFiction;
        else if (genreStr == "Biography") genre = Genre::Biography;
        else throw runtime_error("Invalid genre: " + genreStr);

        if (type == "Printed") {
            int pages;
            iss >> pages;
            books.push_back(new PrintedBook(title, author, genre, pages));
        } 
        else if (type == "EBook") {
            double size;
            iss >> size;
            books.push_back(new EBook(title, author, genre, size));
        }
    }
    bookFile.close(); // Close AFTER the loop

    // Load patrons (Moved OUTSIDE the book loop)
    ifstream patronFile("patrons.txt");
    if (!patronFile) {
        throw runtime_error("Can't open or find patrons.txt");
    }

    while (getline(patronFile, line)) {
        istringstream iss(line);
        int id;
        string name;
        char comma;

     
        if (!(iss >> id >> comma)) continue; 
        getline(iss, name);

        patrons.push_back(new Patron(name, id));
    }
    patronFile.close();
}

void Library::saveData() {
    ofstream bookFile("books.txt");
    if (!bookFile) throw runtime_error("Failed to open books.txt for writing");

    for (const Book* b : books) {
        string genreStr;
        switch(b->getGenre()) {
            case Genre::Fiction: genreStr = "Fiction"; break;
            case Genre::NonFiction: genreStr = "NonFiction"; break;
            case Genre::Mystery: genreStr = "Mystery"; break;
            case Genre::ScienceFiction: genreStr = "Science Fiction"; break;
            case Genre::Biography: genreStr = "Biography"; break;
        }

         bookFile << b->getTitle() << "," << b->getAuthor() << "," << genreStr << ",";

        const EBook* ebook = dynamic_cast<const EBook*>(b);
        const PrintedBook* printed = dynamic_cast<const PrintedBook*>(b);

        if (ebook) {
            bookFile << "EBook," << ebook->getFileSize() << endl;
        } else if (printed) {
            bookFile << "Printed," << printed->getPageCount() << endl;
        }
    }
    bookFile.close();

    ofstream transFile("transactions.txt");
    if (!transFile) throw runtime_error("Failed to open transactions.txt for writing");

    for (const Transaction& t : transactions) {
        transFile << t.getPatronId() << "," << t.getBookTitle() << "," << t.getDate() << endl;
    }
    // transFile closes automatically when going out of scope
}

void Library::borrowBook(int patronId, const string& title) {
    Patron* patron = nullptr;
    for (Patron* p : patrons) {
        if (p->getId() == patronId) {
            patron = p; // Fixed: Removed '&'
            break;
        }
    }
    
    if (!patron) {
        throw runtime_error("Patron not found");
    }

    Book* book = nullptr;
    for (Book* b : books) {
        if (b->getTitle() == title) {
            book = b; 
            break;
        }
    }
    if (!book) { 
        throw runtime_error("Book not found");
    }

    patron->borrowBook(book);
    transactions.emplace_back(patronId, title);
}

void Library::returnBook(int patronId, const string& title) {
    Patron* patron = nullptr;
    for (Patron* p : patrons) {
        if (p->getId() == patronId) {
            patron = p; 
            break;
        }
    }
    
    if (!patron) {
        throw runtime_error("Patron not found");
    }

    Book* book = nullptr;
    for (Book* b : books) {
        if (b->getTitle() == title) {
            book = b; 
            break;
        }
    }
    if (!book) { 
        throw runtime_error("Book not found");
    }

    patron->returnBook(book);
    transactions.emplace_back(patronId, title + "Returned"); //for returns
}

void Library::displayBooks() const {
    for (const Book* b : books) {
        b->displayInfo();
        cout << endl;
    }
}

void Library::displayPatrons() const {
    for (const Patron* p : patrons) {
        p->displayPatron();
        cout << endl;
    }
}

void Library::displayTransactions() const {
    for (const Transaction& t : transactions) {
        t.displayTransaction();
    }
}

vector<Book*> Library::searchByGenre(Genre genre) const {
    vector<Book*> results;
    for (Book* b : books) {
        if (b->getGenre() == genre) {
            results.push_back(b);
        }
    }
    return results;
}

vector<Book> Library::searchByAuthor(const string& author) const {
    vector<Book> results;
    for (const Book* b : books) {
        if (b->getAuthor() == author) {
            results.push_back(*b); // Store a copy of the book
        }
    }
    return results;
}
    
