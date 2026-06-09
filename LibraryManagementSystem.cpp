#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

/*
  Library Management System
  Description:
    This program implements a Library Management System with OOP principles.
    Features:
      - Manage Books (Title, Author, ISBN, multiple copies)
      - Manage Users (ID, Name, Contact)
      - Borrow and Return books
      - Track transactions with timestamp
      - Search books/users
      - Sort books by Title or Author
*/

// ------------------- Book Class -------------------
class Book
{
private:
    string title;
    string author;
    string isbn;
    int totalCopies;
    int availableCopies;

public:
    Book(string t, string a, string i, int copies)
        : title(t), author(a), isbn(i), totalCopies(copies), availableCopies(copies) {}

    // Getter methods
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    int getAvailableCopies() const { return availableCopies; }
    int getTotalCopies() const { return totalCopies; }

    // Check availability
    bool isAvailable() const { return availableCopies > 0; }

    // Borrow/Return book
    void borrowBook()
    {
        if (availableCopies > 0)
            availableCopies--;
    }
    void returnBook()
    {
        if (availableCopies < totalCopies)
            availableCopies++;
    }

    // Display book info
    void display() const
    {
        cout << "ISBN: " << isbn
             << " | Title: " << title
             << " | Author: " << author
             << " | Available Copies: " << availableCopies
             << " / Total Copies: " << totalCopies << "\n";
    }
};

// ------------------- User Class -------------------
class User
{
private:
    string id;
    string name;
    string contact;

public:
    User(string i, string n, string c) : id(i), name(n), contact(c) {}

    string getId() const { return id; }
    string getName() const { return name; }

    void display() const
    {
        cout << "ID: " << id << " | Name: " << name
             << " | Contact: " << contact << "\n";
    }
};

// ------------------- Transaction Class -------------------
class Transaction
{
private:
    string userId;
    string isbn;
    string action; // Borrowed/Returned
    string timestamp;

public:
    Transaction(string u, string i, string a) : userId(u), isbn(i), action(a)
    {
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline
    }

    void display() const
    {
        cout << "UserID: " << userId
             << " | ISBN: " << isbn
             << " | Action: " << action
             << " | Time: " << timestamp << "\n";
    }
};

// ------------------- Library Class -------------------
class Library
{
private:
    vector<Book> books;
    vector<User> users;
    vector<Transaction> transactions;

public:
    // Add book to library
    void addBook()
    {
        string isbn, title, author;
        int copies;
        cout << "Enter ISBN: ";
        cin >> isbn;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Number of Copies: ";
        cin >> copies;
        books.push_back(Book(title, author, isbn, copies));
        cout << "Book added successfully with " << copies << " copies.\n";
    }

    // Add user
    void addUser()
    {
        string id, name, contact;
        cout << "Enter User ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Contact: ";
        getline(cin, contact);
        users.push_back(User(id, name, contact));
        cout << "User added successfully.\n";
    }

    // Borrow a book
    void borrowBook()
    {
        string userId, isbn;
        cout << "Enter User ID: ";
        cin >> userId;
        cout << "Enter Book ISBN: ";
        cin >> isbn;

        Book *book = nullptr;
        for (auto &b : books)
        {
            if (b.getISBN() == isbn)
            {
                book = &b;
                break;
            }
        }

        if (!book)
        {
            cout << "Book not found.\n";
            return;
        }
        if (!book->isAvailable())
        {
            cout << "No copies available.\n";
            return;
        }

        book->borrowBook();
        transactions.push_back(Transaction(userId, isbn, "Borrowed"));
        cout << "Book borrowed successfully.\n";
    }

    // Return a book
    void returnBook()
    {
        string userId, isbn;
        cout << "Enter User ID: ";
        cin >> userId;
        cout << "Enter Book ISBN: ";
        cin >> isbn;

        Book *book = nullptr;
        for (auto &b : books)
        {
            if (b.getISBN() == isbn)
            {
                book = &b;
                break;
            }
        }

        if (!book)
        {
            cout << "Book not found.\n";
            return;
        }
        if (book->getAvailableCopies() == book->getTotalCopies())
        {
            cout << "All copies are already in the library.\n";
            return;
        }

        book->returnBook();
        transactions.push_back(Transaction(userId, isbn, "Returned"));
        cout << "Book returned successfully.\n";
    }

    // Display books
    void listBooks() const
    {
        if (books.empty())
        {
            cout << "No books available.\n";
            return;
        }
        for (const auto &b : books)
            b.display();
    }

    // Display users
    void listUsers() const
    {
        if (users.empty())
        {
            cout << "No users found.\n";
            return;
        }
        for (const auto &u : users)
            u.display();
    }

    // Display transactions
    void listTransactions() const
    {
        if (transactions.empty())
        {
            cout << "No transactions yet.\n";
            return;
        }
        for (const auto &t : transactions)
            t.display();
    }

    // --- Search Functions ---
    void searchBookByTitle() const
    {
        string query;
        cin.ignore();
        cout << "Enter title to search: ";
        getline(cin, query);
        bool found = false;
        for (const auto &b : books)
        {
            if (b.getTitle().find(query) != string::npos)
            {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No books found.\n";
    }

    void searchBookByAuthor() const
    {
        string query;
        cin.ignore();
        cout << "Enter author to search: ";
        getline(cin, query);
        bool found = false;
        for (const auto &b : books)
        {
            if (b.getAuthor().find(query) != string::npos)
            {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No books found.\n";
    }

    void searchBookByISBN() const
    {
        string query;
        cout << "Enter ISBN to search: ";
        cin >> query;
        bool found = false;
        for (const auto &b : books)
        {
            if (b.getISBN() == query)
            {
                b.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "No books found.\n";
    }

    void searchUserByName() const
    {
        string query;
        cin.ignore();
        cout << "Enter user name to search: ";
        getline(cin, query);
        bool found = false;
        for (const auto &u : users)
        {
            if (u.getName().find(query) != string::npos)
            {
                u.display();
                found = true;
            }
        }
        if (!found)
            cout << "No users found.\n";
    }

    void searchUserByID() const
    {
        string query;
        cout << "Enter user ID to search: ";
        cin >> query;
        bool found = false;
        for (const auto &u : users)
        {
            if (u.getId() == query)
            {
                u.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "No users found.\n";
    }

    // --- Sorting Functions ---
    void sortBooksByTitle()
    {
        sort(books.begin(), books.end(), [](Book a, Book b)
             { return a.getTitle() < b.getTitle(); });
        cout << "Books sorted by title.\n";
    }

    void sortBooksByAuthor()
    {
        sort(books.begin(), books.end(), [](Book a, Book b)
             { return a.getAuthor() < b.getAuthor(); });
        cout << "Books sorted by author.\n";
    }
};

// ------------------- Main Function -------------------
int main()
{
    Library lib;
    int choice;

    while (true)
    {
        cout << "\n===== Library Menu =====\n";
        cout << "1. Add Book\n2. Add User\n3. List Books\n4. List Users\n";
        cout << "5. Borrow Book\n6. Return Book\n7. List Transactions\n";
        cout << "8. Search Book by Title\n9. Search Book by Author\n10. Search Book by ISBN\n";
        cout << "11. Search User by Name\n12. Search User by ID\n";
        cout << "13. Sort Books by Title\n14. Sort Books by Author\n15. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.addUser();
            break;
        case 3:
            lib.listBooks();
            break;
        case 4:
            lib.listUsers();
            break;
        case 5:
            lib.borrowBook();
            break;
        case 6:
            lib.returnBook();
            break;
        case 7:
            lib.listTransactions();
            break;
        case 8:
            lib.searchBookByTitle();
            break;
        case 9:
            lib.searchBookByAuthor();
            break;
        case 10:
            lib.searchBookByISBN();
            break;
        case 11:
            lib.searchUserByName();
            break;
        case 12:
            lib.searchUserByID();
            break;
        case 13:
            lib.sortBooksByTitle();
            break;
        case 14:
            lib.sortBooksByAuthor();
            break;
        case 15:
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
