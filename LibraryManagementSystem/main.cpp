#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class BookCopy;

class Library {
    public:
};

class Book {
private:
    string book_id;
    string title;
    vector<string> authors;
    vector<string> publishers;
    vector<BookCopy> copies;  // Vector to store multiple copies of the book

    // Helper function to parse a comma-separated string into a vector
    void parse_list(vector<string>& list, const string& str) {
        stringstream ss(str);
        string item;
        while (getline(ss, item, ',')) {
            list.push_back(item);
        }
    }

public:
    // Constructor
    Book(string book_id, string title, const string& authors_str, const string& publishers_str)
        : book_id(book_id), title(title) {
        parse_list(authors, authors_str);
        parse_list(publishers, publishers_str);
    }

    // Method to add a copy of the book
    void addCopy(const BookCopy& copy) {
        copies.push_back(copy);
    }

    // Method to remove a copy of the book
    void removeCopy(const string& copy_id) {
        for (auto it = copies.begin(); it != copies.end(); ++it) {
            if (it->getCopyID() == copy_id) {
                copies.erase(it);
                break;
            }
        }
    }

    // Getter functions
    string getBookID() const {
        return book_id;
    }

    string getTitle() const {
        return title;
    }

    vector<string> getAuthors() const {
        return authors;
    }

    vector<string> getPublishers() const {
        return publishers;
    }

    vector<BookCopy> getCopies() const {
        return copies;
    }

    // Display book information
    void displayBookInfo() const {
        cout << "Book ID: " << book_id << endl;
        cout << "Title: " << title << endl;

        cout << "Authors: ";
        for (const string& author : authors) {
            cout << author << " ";
        }
        cout << endl;

        cout << "Publishers: ";
        for (const string& publisher : publishers) {
            cout << publisher << " ";
        }
        cout << endl;

        cout << "Copies: " << endl;
        for (const BookCopy& copy : copies) {
            cout << "  Copy ID: " << copy.getCopyID() << ", Rack: " << copy.getRackNumber() 
                 << ", Borrowed: " << (copy.isBorrowed() ? "Yes" : "No") << endl;
        }
    }
};

class BookCopy {
    string copy_id;
    int rack_number;
    bool is_borrowed;
    string due_date;
    public:
        BookCopy(string copy_id, int rack_number)
        : copy_id(copy_id), rack_number(rack_number), is_borrowed(false), due_date("") {}

        string getCopyID() const {
            return copy_id;
        }

        int getRackNumber() const {
            return rack_number;
        }

        bool isBorrowed() const {
            return is_borrowed;
        }

        string getDueDate() const {
            return due_date;
        }

        void borrow(const string& due_date) {
            if (!is_borrowed) {
                is_borrowed = true;
                this->due_date = due_date;
                cout << "Book copy " << copy_id << " has been borrowed. Due date: " << due_date << endl;
            } else {
                cout << "Book copy " << copy_id << " is already borrowed." << endl;
            }
        }

        void return_copy() {
            if (is_borrowed) {
                is_borrowed = false;
                this->due_date = "";
                cout << "Book copy " << copy_id << " has been returned. " << endl;
            } else {
                cout << "Book copy " << copy_id << " is not Borrowed." << endl;
            }
        }
    
        void displayInfo() const {
            cout << "Copy ID: " << copy_id << ", Rack Number: " << rack_number 
                << ", Borrowed: " << (is_borrowed ? "Yes" : "No");
            if (is_borrowed) {
                cout << ", Due Date: " << due_date;
            }
            cout << endl;
        }
};

class Rack {
private:
    int rack_number;               // Unique identifier for the rack
    vector<BookCopy*> book_copies; // Vector to store multiple book copies

public:
    // Constructor
    Rack(int rack_number) : rack_number(rack_number) {}

    // Method to place a book copy on the rack
    void placeBookCopy(BookCopy* copy) {
        book_copies.push_back(copy);
        cout << "Placed book copy " << copy->getCopyID() << " on rack " << rack_number << "." << endl;
    }

    // Method to remove a book copy from the rack
    void removeBookCopy(const string& copy_id) {
        for (auto it = book_copies.begin(); it != book_copies.end(); ++it) {
            if ((*it)->getCopyID() == copy_id) {
                book_copies.erase(it);
                cout << "Removed book copy " << copy_id << " from rack " << rack_number << "." << endl;
                return;
            }
        }
        cout << "Book copy " << copy_id << " not found on rack " << rack_number << "." << endl;
    }

    // Method to check if the rack is empty
    bool isEmpty() const {
        return book_copies.empty();
    }

    // Method to get the rack number
    int getRackNumber() const {
        return rack_number;
    }

    // Method to get all the book copies currently on the rack
    vector<BookCopy*> getBookCopies() const {
        return book_copies;
    }

    // Method to display all the book copies on the rack
    void displayRackContents() const {
        cout << "Rack " << rack_number << " contains " << book_copies.size() << " book copies." << endl;
        for (const auto& copy : book_copies) {
            copy->displayInfo();
        }
    }
};

class User {
    string user_id;
    string name;
    vector<BookCopy*>borrowed_books;
    public:
        User(string user_id, string name) : user_id(user_id), name(name) {}

        string getUserID() const {
            return user_id;
        }

        // Getter for name
        string getName() const {
            return name;
        }

        void borrowBook(BookCopy* book_copy) {
            if (borrowed_books.size() < 5) {
                borrowed_books.push_back(book_copy);
                cout << "User " << name << " borrowed book copy " << book_copy->getCopyID() << "." << endl;
            } else {
                cout << "User " << name << " has already borrowed the maximum number of books." << endl;
            }
        }

        void returnBook(const string& copy_id) {
            for (auto it = borrowed_books.begin(); it != borrowed_books.end(); ++it) {
                if ((*it)->getCopyID() == copy_id) {
                    borrowed_books.erase(it);
                    cout << "User " << name << " returned book copy " << copy_id << "." << endl;
                    return;
                }
            }
            cout << "Book copy " << copy_id << " not found in user's borrowed list." << endl;
        }

        void printBorrowedBooks() const {
            cout << "User " << name << " has borrowed the following books:" << endl;
            for (const auto& book_copy : borrowed_books) {
                cout << "- " << book_copy->getCopyID() << endl;
            }
        }

};

int main(){

    return 0;
}