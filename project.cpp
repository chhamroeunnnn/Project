#include<iostream>
#include<iomanip>
#include<sstream>
#include<vector>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;

// Structure to represent a payment student
struct Payment_Student
{
    int studentID;
    int age;
    int current_year;
    string studentname;
    string Depart_ment;
    float Payment_Amount;
    int imp_day, imp_month, imp_year;
    string sex;
    string Payment_Method;
    Payment_Student *link;  // Pointer to the next Payment_Student in the list
};

// Structure to manage a list of Payment_Student records
struct listpayment_Student
{
    int n; // Number of students in the list
    Payment_Student *head; // Pointer to the first student in the list
    Payment_Student *tail; // Pointer to the last student in the list
};

// Structure to manage deleted students
struct Deleted_Students
{
    int n; // Number of deleted students
    Payment_Student *head; // Pointer to the first deleted student
    Payment_Student *tail; // Pointer to the last deleted student
};

// Function to create a new list of students
listpayment_Student* cretelistStudent() {
    listpayment_Student *t = new listpayment_Student();
    t->n = 0;
    t->head = NULL;
    t->tail = NULL;
    return t;
}

// Function to create a new list of deleted students
Deleted_Students* createDeletedStudentsList() {
    Deleted_Students *d = new Deleted_Students();
    d->n = 0;
    d->head = NULL;
    d->tail = NULL;
    return d;
}

// Function to add a student to the list
void addStudentInformation(listpayment_Student* list, int studentID, int age, const string& studentName,int current_year, string sex,const string& Depart_ment, float Paymenta_Amount, int impDay, int impMonth, int impYear, const string& payment_Method) {
    Payment_Student* newStudent = new Payment_Student();
    newStudent->studentID = studentID;
    newStudent->age = age;
    newStudent->studentname = studentName;
    newStudent->current_year = current_year;
    newStudent->sex = sex;
    newStudent->Depart_ment= Depart_ment;
    newStudent->imp_day = impDay;
    newStudent->imp_month = impMonth;
    newStudent->imp_year = impYear;
    newStudent->Payment_Method = payment_Method;

    // Set Payment_Amoung based on sex
    if (sex == "M") {
        cout << "Select payment option for Male (M):" << endl;
        cout << "1. Pay for a year 600$" << endl;
        cout << "2. Pay for half of year 300$" << endl;
        int choice;
        cout << "Enter choice (1 or 2): ";
        cin >> choice;
        if (choice == 1) {
            newStudent->Payment_Amount = 600;
        } else if (choice == 2) {
            newStudent->Payment_Amount = 300;
        } else {
            cout << "Invalid choice. Defaulting to 300$" << endl;
            newStudent->Payment_Amount = 300;
        }
    } else if (sex == "F") {
        cout << "Select payment option for Female (F):" << endl;
        cout << "1. Pay for a year 450$" << endl;
        cout << "2. Pay for half year 225$" << endl;
        int choice;
        cout << "Enter choice (1 or 2): ";
        cin >> choice;
        if (choice == 1) {
            newStudent->Payment_Amount = 450;
        } else if (choice == 2) {
            newStudent->Payment_Amount = 225;
        } else {
            cout << "Invalid choice. Defaulting to 225$" << endl;
            newStudent->Payment_Amount = 225;
        }
    } else {
        cout << "Invalid sex input. Defaulting to 300$" << endl;
        newStudent->Payment_Amount = 300;
    }

    newStudent->link = nullptr;

    if (list->n == 0) {
        list->head = newStudent;
        list->tail = newStudent;
    } else {
        list->tail->link = newStudent;
        list->tail = newStudent;
    }
    list->n++;
    cout << "Student add information is already thank you!\n"<< endl;
}

// Function to display all students
void ShowAllStudent(listpayment_Student *t) {
    Payment_Student *p = t->head;
    cout << "================================================" << endl;
    cout << "| This is All Student Information in the School |" << endl;
    cout << "================================================" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|  STUDENT_ID  | AGE |   STUDENT_NAME   | CURRENT_YEAR | SEX | DPARTMENT | PAY.AMOUND | INPUT_DAY | INPUT_MONTH | INPUT_YEAR | PAYMENT_METHOD |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while (p != NULL) {
        cout << "| " << setw(13) << left << p->studentID
             << "| " << setw(4)  << left << p->age
             << "| " << setw(17) << left << p->studentname
             << "| " << setw(13)  << left << p->current_year
             << "| " << setw(4)  << left << p->sex
             << "| " << setw(10)  << left << p->Depart_ment
             << "| " << setw(11) << left << p->Payment_Amount
             << "| " << setw(10) << left << p->imp_day
             << "| " << setw(12) << left << p->imp_month
             << "| " << setw(11) << left << p->imp_year
             << "| " << setw(15) << left << p->Payment_Method << "|" << endl;
        p = p->link;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
}

// Function to search for a student by ID
Payment_Student* SerchstudentID(listpayment_Student* t, int IDsearch) {
    Payment_Student* p = t->head;
    while (p != nullptr) {
        if (p->studentID == IDsearch) {
            cout << "StudentID: " << IDsearch << " found" << endl;
            return p;
        }
        p = p->link;
    }
    cout << "StudentID: " << IDsearch << " Not Found" << endl;
    return nullptr;
}

// Function to delete a student by ID
void deletedstudent(listpayment_Student* t, int ID, Deleted_Students* deletedList) {
    Payment_Student* current = t->head;
    Payment_Student* previous = NULL;

    while (current != NULL && current->studentID != ID) {
        previous = current;
        current = current->link;
    }

    if (current != NULL) {
        if (previous == NULL) {
            t->head = current->link;
        } else {
            previous->link = current->link;
        }

        if (current == t->tail) {
            t->tail = previous;
        }

        // Add the deleted student to the deleted students list
        if (deletedList->n == 0) {
            deletedList->head = current;
            deletedList->tail = current;
            current->link = nullptr;
        } else {
            deletedList->tail->link = current;
            deletedList->tail = current;
            current->link = nullptr;
        }

        deletedList->n++;

        t->n--;
        cout<< "Student deleted with this ID:" << ID << endl ;
    } else {
        cout << "No student found with ID: " << ID << endl;
    }
}

// Function to display all deleted students
void ShowDeletedStudents(Deleted_Students* deletedList) {
    Payment_Student* p = deletedList->head;

    if (deletedList->n == 0) {
        cout << "NO STUDENT HAVE BEEN DELETED." << endl;
    } else {
        cout << "===================================================" << endl;
        cout << "| THIS IS ALL INFORMATION THE STUDENT WAS DELETED |" << endl;
        cout << "===================================================" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "|  STUDENT_ID  | AGE |   STUDENT_NAME   | CURRENT_YEAR | SEX | DPARTMENT | PAY.AMOUND | INPUT_DAY | INPUT_MONTH | INPUT_YEAR | PAYMENT_METHOD | " << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
        while (p != NULL) {
        cout << "| " << setw(13) << left << p->studentID
             << "| " << setw(4)  << left << p->age
             << "| " << setw(17) << left << p->studentname
             << "| " << setw(13)  << left << p->current_year
             << "| " << setw(4)  << left << p->sex
             << "| " << setw(10)  << left << p->Depart_ment
             << "| " << setw(11) << left << p->Payment_Amount
             << "| " << setw(10) << left << p->imp_day
             << "| " << setw(12) << left << p->imp_month
             << "| " << setw(11) << left << p->imp_year
             << "| " << setw(15) << left << p->Payment_Method << "|" << endl;
            p = p->link;
        }
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;
    }
}

// Function to write all student information to a CSV file
void write_to_file(listpayment_Student* t) {
    fstream myfile;
    myfile.open("test.csv", ios::app);
    if (!myfile.is_open()){
        cout << "Failed to open file for writing." << endl;
        return;
    }

    // Move to the last student in the list
    Payment_Student *current = t->tail;

    if (current != NULL) {
        myfile << current->studentID << ","
               << current->age << ","
               << current->studentname << ","
               << current->current_year << ","
               << current->sex << ","
               << current->Depart_ment << ","
               << current->Payment_Amount << ","
               << current->imp_day << ","
               << current->imp_month << ","
               << current->imp_year << ","
               << current->Payment_Method << "\n";

        cout << "Student information successfully written to CSV file." << endl;
    } else {
        cout << "No student information available to write." << endl;
    }

    myfile.close();
}


// Function to read and display student information from a CSV file
void displayCSV(const string& studentinformation) {
    ifstream file(studentinformation);
    if (!file.is_open()) {
        cout << "Failed to open file for reading." << endl;
        return;
    }

    string line;

    // Read and display header if present
    if (getline(file, line)) {
        cout << "================================================" << endl;
        cout << "| Student Information from CSV File            |" << endl;
        cout << "================================================" << endl;

        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "|  STUDENT_ID  | AGE |   STUDENT_NAME   | CURRENT_YEAR | SEX | DEPARTMENT | PAY.AMOUNT | INPUT_DAY | INPUT_MONTH | INPUT_YEAR | PAYMENT_METHOD |" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    } else {
        cout << "Empty file or header not found." << endl;
        file.close();
        return;
    }

    // Read and display each subsequent line of data
    while (getline(file, line)) {
        stringstream ss(line);
        int studentID, age, current_year;
        float Payment_Amount;
        string studentname, Payment_Method, Department;
        string sex;
        int imp_day, imp_month, imp_year;

        ss >> studentID;
        ss.ignore(1, ',');
        ss >> age;
        ss.ignore(1, ',');
        getline(ss, studentname, ',');
        ss >> current_year;
        ss.ignore(1, ',');
        getline(ss, sex, ',');
        getline(ss, Department, ',');
        ss >> Payment_Amount;
        ss.ignore(1, ',');
        ss >> imp_day;
        ss.ignore(1, ',');
        ss >> imp_month;
        ss.ignore(1, ',');
        ss >> imp_year;
        ss.ignore(1, ',');
        getline(ss, Payment_Method, ',');

        cout  << "| " << setw(13) << left << studentID
              << "| " << setw(4)  << left << age
              << "| " << setw(17) << left << studentname
              << "| " << setw(13)  << left << current_year
              << "| " << setw(4)  << left << sex
              << "| " << setw(11)  << left << Department
              << "| " << setw(11) << left << Payment_Amount
              << "| " << setw(10) << left << imp_day
              << "| " << setw(12) << left << imp_month
              << "| " << setw(11) << left << imp_year
              << "| " << setw(15) << left << Payment_Method << "|" << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------\n" << endl;

    file.close();
}
// Main function for user input (but only small leter)
int main() {
    cout << "\t[=============Welcome to our School=============]\n" << endl;
    int studentID, age, current_year;
    string studentname, sex, Depart_ment, Payment_Method;
    float Payment_Amount;
    int imp_day, imp_month, imp_year;

    listpayment_Student *n = cretelistStudent(); // Create a new list of students
    Deleted_Students *deletedList = createDeletedStudentsList(); // Create a new list of deleted students

    char menu;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\t\033[1;44m===========*:Menu:*============\033[0m\n" << endl;
        cout << "\033[1;36m[a]. |Add Information Student|\033[0m\n" << endl;
        cout << "\033[1;36m[b]. |Display Student information|\033[0m\n" << endl;
        cout << "\033[1;36m[c]. |Search Student by ID|\033[0m\n" << endl;
        cout << "\033[1;36m[d]. |Delete Student by ID|\033[0m\n" << endl;
        cout << "\033[1;36m[e]. |Display all deleted students|\033[0m\n" << endl;
        cout << "\033[1;36m[f]. |Store all student in CSV file|\033[0m\n" << endl;
        cout << "\033[1;36m[g]. |Read data from CSV file|\033[0m\n" << endl;
        cout << "\033[1;36m[h]. |Exit|\033[0m" << endl;

        cout << "\n======={Please check follow by our structure}======" << endl;
        cout << "\t\033[1;35mEnter option in a small letter only: \033[0m";
        cin >> menu;

        switch (menu) {
            case 'a': // Option a: Add Information Student
                // Input student details and add them
                cout << "studentID: ";
                cin >> studentID;
                cout << "Age: ";
                cin >> age;
                cout << "Current_year: ";
                cin >> current_year;
                cout << "studentname: ";
                cin.ignore(); // Ignore newline character left in stream
                getline(cin, studentname);
                cout << "Sex (M/F): ";
                cin >> sex;
                cout << "Depart_ment: ";
                cin >> Depart_ment;
                cout << "payment_Date (day month year): ";
                cin >> imp_day >> imp_month >> imp_year;
                cout << "Payment_Method: ";
                cin >> Payment_Method; 
                addStudentInformation(n, studentID, age, studentname, current_year, sex, Depart_ment, Payment_Amount, imp_day, imp_month, imp_year, Payment_Method);
                break;

            case 'b': // Option b: Display Student information
                ShowAllStudent(n);
                break;

            case 'c':  // Option c: Search Student by ID
                cout << "Enter student ID to search: ";
                cin >> studentID;
                {
                    Payment_Student* foundStudent = SerchstudentID(n, studentID);
                    if (foundStudent != NULL) {
                        cout << "Student ID: " << studentID << " found." << endl;
                        cout << "Student Name: " << foundStudent->studentname << endl;
                    } else {
                        cout << "No Student found with ID: " << studentID << endl;
                    }
                }
                break;

            case 'd': // Option d: Delete Student by ID
                int studentID;
                cout << "Enter student ID to delete: ";
                cin >> studentID;
                deletedstudent(n, studentID, deletedList);
                break;

            case 'e': // Option e: Display all deleted students
                ShowDeletedStudents(deletedList);
                break;

            case 'f': // Option f: Store all student in CSV file
                write_to_file(n);
                cout << "Data written to CSV file.\n";
                break;

            case 'g': // Option g: Read data from CSV file
                cout << "Displaying student information from CSV file:\n";
                displayCSV("test.csv");
                break;

            case 'h':
                cout << "Exiting program...\n";
                exitProgram = true; // Set exit flag to true to terminate the loop
                break;

            default:
                cout << "Invalid option! Please enter a valid option (a->h).\n";
        }

        cout << endl; // Add a newline for better readability after each operation
    }

    return 0;
}



