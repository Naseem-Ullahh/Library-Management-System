# 📚 Library Management System

A console-based Library Management System implemented in C++ using Object-Oriented Programming (OOP) principles. Developed as part of the **Data Structures & Algorithms (DSA)** course.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Classes & Design](#classes--design)
- [How to Compile & Run](#how-to-compile--run)
- [Menu Options](#menu-options)
- [Sample Usage](#sample-usage)
- [Data Structures Used](#data-structures-used)
- [Algorithms Used](#algorithms-used)
- [Limitations & Future Improvements](#limitations--future-improvements)

---

## Overview

This program simulates a real-world library system where books can be added, borrowed, and returned by registered users. All transactions are logged with timestamps. The system also supports searching and sorting for efficient book/user lookup.

---

## Features

- Add and manage **books** with multiple copies
- Register and manage **users**
- **Borrow and return** books with availability tracking
- **Transaction logging** with real-time timestamps
- **Search** books by Title, Author, or ISBN
- **Search** users by Name or ID
- **Sort** books alphabetically by Title or Author

---

## Project Structure

```
LibraryManagementSystem/
│
├── main.cpp          # Full source code
└── README.md         # Project documentation
```

---

## Classes & Design

The system follows OOP principles with four core classes:

### `Book`
Manages book information and copy tracking.

|    Member         | Type     | Description                |
|-------------------|----------|----------------------------|
| `title`           | `string` | Book title                 |
| `author`          | `string` | Author name                |
| `isbn`            | `string` | Unique identifier          |
| `totalCopies`     | `int`    | Total copies owned         |
| `availableCopies` | `int`    | Copies currently available |

Key methods: `borrowBook()`, `returnBook()`, `isAvailable()`, `display()`

---

### `User`
Stores library member information.

| Member    | Type     | Description         |
|-----------|----------|---------------------|
| `id`      | `string` | Unique user ID      |
| `name`    | `string` | User's full name    |
| `contact` | `string` | Contact information |

---

### `Transaction`
Records every borrow/return action with a timestamp.

| Member      | Type     | Description                  |
|-------------|----------|------------------------------|
| `userId`    | `string` | ID of the user               |
| `isbn`      | `string` | ISBN of the book             |
| `action`    | `string` | "Borrowed" or "Returned"     |
| `timestamp` | `string` | Date and time of transaction |

---

### `Library`
The central controller class. Holds all books, users, and transactions in `vector` containers and provides all operations via a menu-driven interface.

---

## How to Compile & Run

### Prerequisites
- Any C++ compiler supporting C++11 or later (e.g., g++, MSVC, clang++)

### Compile (Linux / macOS)
```bash
g++ -o library main.cpp -std=c++11
./library
```

### Compile (Windows)
```bash
g++ -o library.exe main.cpp -std=c++11
library.exe
```

---

## Menu Options

```
===== Library Menu =====
 1.  Add Book
 2.  Add User
 3.  List Books
 4.  List Users
 5.  Borrow Book
 6.  Return Book
 7.  List Transactions
 8.  Search Book by Title
 9.  Search Book by Author
10.  Search Book by ISBN
11.  Search User by Name
12.  Search User by ID
13.  Sort Books by Title
14.  Sort Books by Author
15.  Exit
```

---

## Sample Usage

```
Enter choice: 1
Enter ISBN: 978-0-13-468599-1
Enter Title: The C++ Programming Language
Enter Author: Bjarne Stroustrup
Enter Number of Copies: 3
Book added successfully with 3 copies.

Enter choice: 5
Enter User ID: U001
Enter Book ISBN: 978-0-13-468599-1
Book borrowed successfully.
```

---

## Data Structures Used

| Structure                  |            Usage                |
|----------------------------|---------------------------------|
| `std::vector<Book>`        | Dynamic list of all books       |
| `std::vector<User>`        | Dynamic list of all users       |
| `std::vector<Transaction>` | Growing log of all transactions |

---

## Algorithms Used

| Algorithm                            |               Where Applied                                  |
|--------------------------------------|--------------------------------------------------------------|
| **Linear Search**                    | Finding books by ISBN/title/author; finding users by ID/name |
| **std::sort with Lambda Comparator** | Sorting books alphabetically by title or author              |
| **std::string::find**                | Substring matching for title/author/name search queries      |

---

## Limitations & Future Improvements

**Current Limitations:**
- Data is not persisted — all records are lost when the program exits
- No validation to prevent the same user borrowing the same book twice
- No limit on how many books a single user can borrow

**Suggested Improvements:**
- File I/O or SQL integration for persistent storage
- Track which user currently holds which copy of a book
- Implement due dates and overdue fine calculation
- Replace linear search with hash maps (`std::unordered_map`) for O(1) lookups by ISBN/ID
- Add input validation and error handling for edge cases

---

## Author

**Naseem Ullah**
BS Software Engineering — NUST MCS, Rawalpindi
Course: Data Structures & Algorithms
