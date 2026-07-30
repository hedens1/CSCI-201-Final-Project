#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
    int patronId;
    std::string bookTitle;
    std::string date;

public:
    Transaction(int pid, std::string bt);
    void displayTransaction() const;

    int getPatronId() const { return patronId; }
    std::string getBookTitle() const { return bookTitle; }
    std::string getDate() const { return date; }
};

#endif // TRANSACTION_H   