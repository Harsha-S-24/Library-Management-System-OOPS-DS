# Library Management System

The Library Management System is a C++ console application that simulates the operations of a library, allowing both customers and librarians to interact with the library's collection of books. Customers can borrow and return books, while librarians can manage the library's inventory and customers.

## Features

- *Customer Features:*
  - Display available books.
  - Borrow books (with a waiting queue if a book is not available).
  - Return books.
  - Customer ID-based access.

- *Librarian Features (Administration):*
  - Add books to the library.
  - Remove books from the library.
  - Display the library's book collection.
  - Display issued books and their respective customers.
  - Add customers to the library system.
  - Remove customers from the library system.
  - Change librarian password.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)

### Installation

1. Clone the repository:

   ```shell
   git clone https://github.com/Harsha-S-24/Library-Management-System-OOPS-DS.git
Compile the source code:

shell
Copy code
g++ -o library_system main.cpp
Run the application:

shell
Copy code
./library_system
Usage
Upon running the program, you will be prompted to choose your role: Customer or Librarian (Administration).
Customers need to enter their customer ID.
Librarians need to enter the librarian password.