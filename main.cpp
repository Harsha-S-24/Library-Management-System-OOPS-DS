#include <bits/stdc++.h>
using namespace std;

class Book
{
public:
    Book(const string &title, const string &author, int id, int quantity)
        : title(title), author(author), id(id), quantity(quantity) {}

public:
    int getID() const
    {
        return id;
    }
    int getQuantity() const
    {
        return quantity;
    }
    string getTitle() const
    {
        return title;
    }
    string getAuthor() const
    {
        return author;
    }

    void displayInfo() const
    {
        cout << "Book ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Quantity available: " << quantity << endl;
    }

    bool borrowBook(int cust_id)
    {
        if (quantity > 0)
        {
            quantity--;
            issuedTo[cust_id] = title;
            cout << "Book '" << title << "' successfully borrowed by Customer ID " << cust_id << "." << endl;
            return true;
        }
        else
        {
            cout << "Sorry, the book '" << title << "' is currently out of stock.You are added into the queue for the book" << endl;
            return false;
        }
    }

    void returnBook(int cust_id)
    {
        if (issuedTo.find(cust_id) == issuedTo.end())
        {
            cout << "You can't return a book that you haven't borrowed." << endl;
        }
        else
        {
            quantity++;
            issuedTo.erase(cust_id);
            cout << "Book '" << title << "' successfully returned by Customer ID " << cust_id << "." << endl;
        }
    }

    bool isIssued() const
    {
        return !issuedTo.empty();
    }

    int getIssuedTo() const
    {
        return issuedTo.begin()->first;
    }

private:
    int id;
    string title;
    string author;
    int quantity;
    map<int, string> issuedTo;
};

class Customer
{
public:
    Customer(int cust_id, const string &name) : cust_id(cust_id), name(name) {}
    int getID() const
    {
        return cust_id;
    }
    string getName() const
    {
        return name;
    }

    void addToQueue(int bookID)
    {
        bookQueue.push(bookID);
    }
    bool removeFromQueue(int bookID)
    {
        if (bookQueue.empty())
            return false;

        if (bookQueue.front() == bookID)
        {
            bookQueue.pop();
            return true;
        }

        queue<int> tempQueue;
        while (!bookQueue.empty())
        {
            int frontBookID = bookQueue.front();
            bookQueue.pop();
            if (frontBookID != bookID)
            {
                tempQueue.push(frontBookID);
            }
        }

        bookQueue = tempQueue;
        return false;
    }

    bool hasBooksInQueue() const
    {
        return !bookQueue.empty();
    }

    int getNextBookInQueue() const
    {
        return bookQueue.front();
    }

private:
    int cust_id;
    string name;
    queue<int> bookQueue;
};

class Library
{
public:
    void addBook(const string &title, const string &author, int quantity)
    {
        books.emplace_back(title, author, nextBookID++, quantity);
    }

    void removeBook(int bookID)
    {
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->getID() == bookID)
            {
                books.erase(it);
                cout << "Book with ID " << bookID << " removed." << endl;
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found." << endl;
    }

    void displayBooks() const
    {
        if (books.empty())
        {
            cout << "No books in the library." << endl;
        }
        else
        {
            cout << "Library Books:" << endl;
            for (const auto &book : books)
            {
                book.displayInfo();
                cout << "-------------------" << endl;
            }
        }
    }

    void processBookRequests()
    {
        for (auto &customer : customers)
        {
            if (customer.hasBooksInQueue())
            {
                int bookID = customer.getNextBookInQueue();
                Book *book = findBook(bookID);
                if (book && book->getQuantity() > 0)
                {
                    int cust_id = customer.getID();
                    book->borrowBook(cust_id);
                    customer.removeFromQueue(bookID);
                    issuedBooks[cust_id].push_back(book->getTitle());
                }
            }
        }
    }

    void addCustomer(int cust_id, const string &name)
    {
        if (!isCustomerIDUnique(cust_id))
        {
            cout << "Customer ID " << cust_id << " is not unique. Please choose a different ID." << endl;
            return;
        }
        customers.emplace_back(cust_id, name);
    }

    void removeCustomer(int cust_id)
    {
        for (auto it = customers.begin(); it != customers.end(); ++it)
        {
            if (it->getID() == cust_id)
            {
                customers.erase(it);
                cout << "Customer with ID " << cust_id << " removed." << endl;
                return;
            }
        }
        cout << "Customer with ID " << cust_id << " not found." << endl;
    }

    void displayCustomers() const
    {
        if (customers.empty())
        {
            cout << "No customers in the library system." << endl;
        }
        else
        {
            cout << "Library Customers:" << endl;
            for (const auto &customer : customers)
            {
                cout << "Customer ID: " << customer.getID() << endl;
                cout << "Name: " << customer.getName() << endl;
                cout << "-------------------" << endl;
            }
        }
    }

    Book *findBook(int bookID)
    {
        for (auto &book : books)
        {
            if (book.getID() == bookID)
            {
                return &book;
            }
        }
        return nullptr;
    }

    void displayIssuedBooks() const
    {
        if (issuedBooks.empty())
        {
            cout << "No books have been issued." << endl;
        }
        else
        {
            cout << "Issued Books:" << endl;
            for (const auto &entry : issuedBooks)
            {
                cout << "Customer ID: " << entry.first << endl;
                for (const auto &bookTitle : entry.second)
                {
                    cout << "   - " << bookTitle << endl;
                }
            }
        }
    }

    Customer &getCustomer(int cust_id)
    {
        for (auto &customer : customers)
        {
            if (customer.getID() == cust_id)
            {
                return customer;
            }
        }
        throw runtime_error("Customer with ID " + to_string(cust_id) + " not found.");
    }

private:
    vector<Book> books;
    vector<Customer> customers;
    int nextBookID = 1;
    map<int, vector<string>> issuedBooks;
    bool isCustomerIDUnique(int cust_id) const
    {
        for (const auto &customer : customers)
        {
            if (customer.getID() == cust_id)
            {
                return false; // ID is not unique
            }
        }
        return true; // ID is unique
    }
};

class Librarian
{
public:
    Librarian(const string &password) : password(password) {}

    bool authenticate(const string &inputPassword) const
    {
        return inputPassword == password;
    }

    void changePassword(const string &newPassword)
    {
        password = newPassword;
        cout << "Password changed successfully." << endl;
    }

private:
    string password;
};

int main()
{
    Library library;
    Librarian librarian("adminpass"); // Change the password as needed
    int role;

    while (true)
    {

        cout << "Enter your role:" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Librarian (Administration)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your role (1, 2, or 3 to exit): ";
        cin >> role;

        if (role == 1)
        { // Customer
            int cust_id;
            cout << "Enter your customer ID: ";
            cin >> cust_id;

            try
            {
                Customer &customer = library.getCustomer(cust_id);

                int choice;

                do
                {
                    cout << "Customer Menu for " << customer.getName() << ":" << endl;
                    cout << "1. Display Available Books" << endl;
                    cout << "2. Borrow Book" << endl;
                    cout << "3. Return Book" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        library.displayBooks();
                        break;
                    case 2:
                    {
                        int bookID;
                        cout << "Enter the ID of the book to borrow: ";
                        cin >> bookID;
                        Book *book = library.findBook(bookID);
                        if (book)
                        {
                            if (!book->borrowBook(cust_id))
                            {
                                customer.addToQueue(bookID);
                            }
                        }
                        else
                        {
                            cout << "Book with ID " << bookID << " not found." << endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        int bookID;
                        cout << "Enter the ID of the book to return: ";
                        cin >> bookID;
                        Book *book = library.findBook(bookID);
                        if (book)
                        {
                            book->returnBook(cust_id);
                            library.processBookRequests();
                        }
                        else
                        {
                            cout << "Book with ID " << bookID << " not found." << endl;
                        }
                        break;
                    }
                    case 4:
                        cout << "Exiting the program." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }

                } while (choice != 4);
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
        }
        else if (role == 2)
        { // Librarian (Administration)
            string inputPassword;
            cout << "Enter the librarian password: ";
            cin >> inputPassword;

            if (librarian.authenticate(inputPassword))
            {
                int choice;

                do
                {
                    cout << "Librarian Menu (Administration):" << endl;
                    cout << "1. Add Book" << endl;
                    cout << "2. Remove Book" << endl;
                    cout << "3. Display Books" << endl;
                    cout << "4. Display Issued Books" << endl;
                    cout << "5. Add Customer" << endl;
                    cout << "6. Remove Customer" << endl;
                    cout << "7. Display Customers" << endl;
                    cout << "8. Change password" << endl;
                    cout << "9. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                    {
                        string title, author;
                        int quantity;
                        cout << "Enter book title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter book author: ";
                        getline(cin, author);
                        cout << "Enter book quantity: ";
                        cin >> quantity;
                        library.addBook(title, author, quantity);
                        break;
                    }
                    case 2:
                    {
                        int bookID;
                        cout << "Enter the ID of the book to remove: ";
                        cin >> bookID;
                        library.removeBook(bookID);
                        break;
                    }
                    case 3:
                        library.displayBooks();
                        break;
                    case 4:
                        library.displayIssuedBooks();
                        break;
                    case 5:
                    {
                        int student_id;
                        string studentName;
                        cout << "Enter the customer ID: ";
                        cin >> student_id;
                        cout << "Enter the customer name: ";
                        cin.ignore();
                        getline(cin, studentName);
                        library.addCustomer(student_id, studentName);
                        break;
                    }
                    case 6:
                    {
                        int student_id;
                        cout << "Enter the customer ID to remove: ";
                        cin >> student_id;
                        library.removeCustomer(student_id);
                        break;
                    }
                    case 7:
                        library.displayCustomers();
                        break;
                  
                    case 8:
                    {
                        string newPassword;
                        cout << "Enter the new password: ";
                        cin >> newPassword;
                        librarian.changePassword(newPassword);
                        break;
                    }
                    case 9:
                        cout << "Exiting the program." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }

                } while (choice != 8);
            }
            else
            {
                cout << "Authentication failed. Exiting the program." << endl;
                break;
            }
        }
        else if (role == 3)
        {
            cout << "Exiting the program." << endl;
            break;
        }
        else
        {
            cout << "Invalid role. Please try again." << endl;
        }
    }

    return 0;
}