#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ----- Class representing a single person -----
class Person {
private:
    string name;
    string phone;
    string email;

public:
    Person() {}
    Person(string n, string p, string e) : name(n), phone(p), email(e) {}

    // Getters
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    // Display person details
    void display() const {
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
        cout << "Email : " << email << endl;
        cout << "-----------------------------------\n";
    }

    // Save to file in a simple format
    void saveToFile(ofstream &file) const {
        file << name << endl;
        file << phone << endl;
        file << email << endl;
    }

    // Load from file (static factory method)
    static Person loadFromFile(ifstream &file) {
        string n, p, e;
        getline(file, n);
        getline(file, p);
        getline(file, e);
        return Person(n, p, e);
    }
};

// ----- Manager Class -----
class PersonalInfoManager {
private:
    vector<Person> records;
    const string filename = "records.txt";

public:
    PersonalInfoManager() {
        loadFromFile();
    }

    // Add a new record
    void addRecord() {
        string name, phone, email;

        cout << "Enter Name  : ";
        getline(cin, name);
        cout << "Enter Phone : ";
        getline(cin, phone);
        cout << "Enter Email : ";
        getline(cin, email);

        records.push_back(Person(name, phone, email));
        cout << "\nRecord added successfully!\n";
        saveToFile();
    }

    // Display all records
    void displayRecords() {
        if (records.empty()) {
            cout << "\nNo records found!\n";
            return;
        }

        cout << "\n--- Stored Records ---\n";
        for (const auto &p : records) {
            p.display();
        }
    }

    // Search by name
    void searchRecord() {
        string key;
        cout << "Enter name to search: ";
        getline(cin, key);

        bool found = false;
        for (const auto &p : records) {
            if (p.getName() == key) {
                cout << "\nRecord Found:\n";
                p.display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nNo match found!\n";
    }

    // Save all records to file
    void saveToFile() {
        ofstream file(filename);
        for (const auto &p : records) {
            p.saveToFile(file);
            file << "---\n";  // separator
        }
        file.close();
    }

    // Load records from file
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        while (true) {
            string name, phone, email;
            if (!getline(file, name)) break;
            getline(file, phone);
            getline(file, email);
            records.push_back(Person(name, phone, email));
            getline(file, line); // read separator "---"
        }
        file.close();
    }
};

// ----- Main Program -----
int main() {
    PersonalInfoManager manager;
    int choice;

    while (true) {
        cout << "\n====== Digital Personal Information Manager ======\n";
        cout << "1. Add New Record\n";
        cout << "2. View All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // clear newline from buffer

        switch (choice) {
            case 1: manager.addRecord(); break;
            case 2: manager.displayRecords(); break;
            case 3: manager.searchRecord(); break;
            case 4: 
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
