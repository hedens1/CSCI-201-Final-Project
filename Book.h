#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


enum class Genre {
    Fiction,
    NonFiction,
    Mystery,
    ScienceFiction,
    Biography
};

enum class BookStatus {
    Available, 
    CheckedOut
};

class Book {
protected:
    std::string title;
    std::string author;
    Genre genre;
    BookStatus status;

public:
    Book(std::string t, std::string a, Genre g);
    virtual ~Book() = default;

    virtual void displayInfo() const;
    void setStatus(BookStatus s);
    BookStatus getStatus() const;

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    Genre getGenre() const { return genre; }

    bool operator==(const Book& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Book& b);
};

class EBook : public Book {
    double fileSizeMB;
public:
    EBook(std::string t, std::string a, Genre g, double size);
    void displayInfo() const override;
    
    // Fixed typo: gertFileSize -> getFileSize
    double getFileSize() const { return fileSizeMB; }
};

class PrintedBook : public Book {
    int pageCount;
public:
    PrintedBook(std::string t, std::string a, Genre g, int pages);
    void displayInfo() const override;
    int getPageCount() const { return pageCount; }
};

#endif // BOOK_H   