#include "Transaction.h"
#include <sstream>
#include <iomanip>
#include <chrono>   // Added: Required for chrono::system_clock
#include <ctime>    // Added: Required for time_t and localtime
#include <iostream> // Added: Required for cout and endl

using namespace std;

Transaction::Transaction(int pid, string bt) : patronId(pid), bookTitle(bt) {
    
    // Get the current date and time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&now_time);

    // Format the date as "YYYY-MM-DD"
    stringstream ss;
    ss << put_time(&local_tm, "%Y-%m-%d");
    date = ss.str();
}

void Transaction::displayTransaction() const {
    cout << "Patron ID: " << patronId << ", Book Title: " << bookTitle 
         << ", Date: " << date << endl;
}   