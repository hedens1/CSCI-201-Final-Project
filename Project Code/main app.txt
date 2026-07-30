#include <iostream>
#include <limits>
#include "Library.h"
// Function to display the main menu
void displayMenu() {
    std::cout << "\n=== Library Management System ===\n";
    std::cout << "1. View All Books\n";
    std::cout << "2. View All Patrons\n";
    std::cout << "3. Checkout Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. Search by Author\n";
    std::cout << "6. Search by Genre\n";
    std::cout << "7. View Transactions\n";
    std::cout << "8. Save and Exit\n";
    std::cout << "Enter choice: ";
}
// Function to get genre from user input
Genre getGenreFromUser() {
    int choice;
    std::cout << "Select Genre:\n";
    std::cout << "1. Fiction\n2. NonFiction\n3. Mystery\n4. Science\n5. Biography\n";
    std::cout << "Enter selection: ";
    std::cin >> choice;
    
    switch(choice) {
        case 1: return Genre::Fiction;
        case 2: return Genre::NonFiction;
        case 3: return Genre::Mystery;
        case 4: return Genre::ScienceFiction;
        case 5: return Genre::Biography;
        default: throw std::runtime_error("Genre not available.");
    }
}

int main() {
    Library library;
    
    try {
        library.loadData();
        std::cout << "Data loaded successfully!\n";
        
        int choice;
        do {
            displayMenu();
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            
            switch(choice) {
                case 1:
                    library.displayBooks();
                    break;
                    
                case 2:
                    library.displayPatrons();
                    break;
                //Checkout and return book options
                case 3: {
                    int patronId;
                    std::string title;
                    std::cout << "Enter Patron ID: ";
                    std::cin >> patronId;
                    std::cin.ignore();
                    std::cout << "Enter Book Title: ";
                    std::getline(std::cin, title);
                    library.borrowBook(patronId, title);
                    std::cout << "Book checked out successfully!\n";
                    break;
                }
                    
                case 4: {
                    int patronId;
                    std::string title;
                    std::cout << "Enter Patron ID: ";
                    std::cin >> patronId;
                    std::cin.ignore();
                    std::cout << "Enter Book Title: ";
                    std::getline(std::cin, title);
                    library.returnBook(patronId, title);
                    std::cout << "Book returned successfully!\n";
                    break;
                }
                    //search by author 
                case 5: {
                    std::string author;
                    std::cout << "Enter author name: ";
                    std::cin.ignore();
                    std::getline(std::cin, author);
                    auto results = library.searchByAuthor(author);
                    std::cout << "Found " << results.size() << " book(s)\n";
                    for (const auto& b : results) {
                        b.displayInfo();
                        std::cout << "\n";
                    }
                    break;
                }
                    
                case 6: {
                    Genre genre = getGenreFromUser();
                    auto results = library.searchByGenre(genre);
                    std::cout << "Found " << results.size() << " book(s)\n";
                    for (const auto& b : results) {
                        b->displayInfo();
                        std::cout << "\n";
                    }
                    break;
                }
                    
                case 7:
                    library.displayTransactions();
                    break;
                    
                case 8:
                    library.saveData();
                    std::cout << "Data saved. Goodbye!\n";
                    break;
                    
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
            
        } while (choice != 8);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}   