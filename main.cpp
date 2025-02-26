#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Person
{
protected:
    string name;
    string dayOfBirth;
    char sex;
    string phoneNumber;

public:
    Person(string n, string dob, char s, string phone)
        : name(n), dayOfBirth(dob), sex(s), phoneNumber(phone) {}

    string getName() const { return name; }
    string getDayOfBirth() const { return dayOfBirth; }
    char getSex() const { return sex; }
    string getPhoneNumber() const { return phoneNumber; }
};

class Student : public Person
{
private:
    int studentID;
    string Class;

public:
    Student(int id, string n, string dob, char s, string phone, string cls)
        : Person(n, dob, s, phone), studentID(id), Class(cls) {}

    int getStudentID() const { return studentID; }
    void setStudentID(int id) { studentID = id; }
    string getClass() const { return Class; }
    void setClass(string cls) { Class = cls; }

    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << getStudentID() << ",";
            file << getName() << ",";
            file << getDayOfBirth() << ",";
            file << getSex() << ",";
            file << getPhoneNumber() << ",";
            file << getClass() << endl;
            file.close();
            cout << "Student information has been saved to file " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    void displayInfo() const
    {
        cout << "| " << setw(10) << left << getStudentID() << " | "
             << setw(35) << left << getName() << " | "
             << setw(15) << left << getDayOfBirth() << " | "
             << setw(4) << left << getSex() << " | "
             << setw(15) << left << getPhoneNumber() << " | "
             << setw(10) << left << getClass() << " |" << endl;
    }
};

class Book
{
private:
    string title;
    string author;
    int bookID;
    bool available;

public:
    Book(string t, string a, int id, bool avail) : title(t), author(a), bookID(id), available(avail) {}


    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getBookID() const { return bookID; }
    bool isAvailable() const { return available; }

    void borrowBook() { available = false; }
    void returnBook() { available = true; }

    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << getBookID() << ",";
            file << getTitle() << ",";
            file << getAuthor() << ",";
            file << (isAvailable() ? "Available" : "Not Available") << endl;
            file.close();
            cout << "Book information has been saved to file " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    void displayInfo() const
    {
        cout << "| " << setw(10) << left << getBookID() << " | "
             << setw(35) << left << getTitle() << " | "
             << setw(20) << left << getAuthor() << " | "
             << setw(15) << left << (isAvailable() ? "Available" : "Not Available") << " |" << endl;
    }
};

class Loan
{
private:
    int loanID;
    int studentID;
    int bookID;
    string loanDate;
    string returnDate;

public:
    Loan(int lid, int sid, int bid, string ld, string rd = "")
        : loanID(lid), studentID(sid), bookID(bid), loanDate(ld), returnDate(rd) {}

    int getLoanID() const { return loanID; }
    int getStudentID() const { return studentID; }
    int getBookID() const { return bookID; }
    string getLoanDate() const { return loanDate; }
    string getReturnDate() const { return returnDate; }

    void setReturnDate(string rd) { returnDate = rd; }

    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << getLoanID() << ",";
            file << getStudentID() << ",";
            file << getBookID() << ",";
            file << getLoanDate() << ",";
            file << getReturnDate() << endl;
            file.close();
            cout << "Loan information has been saved to file " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    void displayInfo() const
    {
        cout << "| " << setw(10) << left << getLoanID() << " | "
             << setw(10) << left << getStudentID() << " | "
             << setw(10) << left << getBookID() << " | "
             << setw(15) << left << getLoanDate() << " | "
             << setw(15) << left << getReturnDate() << " |" << endl;
    }
};

// Function to read student information from file and display it in a table
void readAndDisplayFromFileMember(const string &filename)
{
    ifstream file(filename);
    string line;

    cout << "| " << setw(10) << left << "ID"
         << " | "
         << setw(35) << left << "Name"
         << " | "
         << setw(15) << left << "Day of birth"
         << " | "
         << setw(4) << left << "Sex"
         << " | "
         << setw(15) << left << "Phone number"
         << " | "
         << setw(10) << left << "Class"
         << " |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ','))
            {
                tokens.push_back(token);
            }
            if (tokens.size() == 6)
            {
                Student student(stoi(tokens[0]), tokens[1], tokens[2], tokens[3][0], tokens[4], tokens[5]);
                student.displayInfo();
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file " << filename << " for reading." << endl;
    }
}


void displayBookTable(const vector<Book>& books)
{
    cout << "| " << setw(10) << left << "ID"
         << " | "
         << setw(35) << left << "Title"
         << " | "
         << setw(20) << left << "Author"
         << " | "
         << setw(15) << left << "Status"
         << " |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;

    for (const auto& book : books)
    {
        book.displayInfo();
    }

    cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

vector<Book> readBooksFromFile(const string& filename)
{
    vector<Book> books;
    ifstream file(filename);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ','))
            {
                tokens.push_back(token);
            }

            if (tokens.size() == 4)
            {
                int bookID = stoi(tokens[0]);
                string title = tokens[1];
                string author = tokens[2];
                bool available = (tokens[3] == "Available");

                Book book(title, author, bookID, available);
                books.push_back(book);
            }
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file " << filename << " for reading." << endl;
    }

    return books;
}



void Member()
{
    int id;
    string name, dob, phone, Class;
    char sex;

    cout << "Enter student information:" << endl;
    cout << "ID: ";
    cin >> id;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Date of Birth (dd/mm/yyyy): ";
    getline(cin, dob);
    cout << "Sex (M/F): ";
    cin >> sex;
    cout << "Phone Number: ";
    cin >> phone;
    cout << "Class: ";
    cin >> Class;

    Student newStudent(id, name, dob, sex, phone, Class);
    newStudent.saveToFile("students.txt");
}

void BookInfo(){
    string title, author;
    int bookID;
    char choice;
    bool isAvailable;

    cout << "Enter book information:" << endl;
    cout << "Title: ";
    cin>> title;
    cout << "Author: ";
    cin>> author;
    cout << "Book ID: ";
    cin >> bookID;
    cin.ignore(); // Ignore newline character

    
    Book newBook(title, author, bookID, isAvailable);
    cout << "Do you want to borrow this book? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        newBook.borrowBook();
        cout << "Book has been borrowed." << endl;
        isAvailable = false;
        
    } else {
        cout << "Book has not been borrowed." << endl;
        isAvailable = true;
    }
    
    // Save book information to file
    newBook.saveToFile("books.txt");

    // Display book information
    cout << "Book Information:" << endl;
    newBook.displayInfo();
}


int main()
{
    int choice;
    do
    {
        cout << "Choose one of the following options:" << endl;
        cout << "1. Enter student information" << endl;
        cout << "2. Read student information from file" << endl;
        cout << "3. Enter book" << endl;
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Member();
        }
        else if (choice == 2)
        {
            readAndDisplayFromFileMember("students.txt");
            vector<Book> books = readBooksFromFile("books.txt");
            displayBookTable(books);
        }
        else if (choice == 3)
        {
           BookInfo();
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
