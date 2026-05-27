#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Passenger class with encapsulation
class Passenger {
public:
    int id;
    string name, flight, seat;
    string destination, date;

    Passenger() : id(0), name(""), flight(""), seat(""), destination(""), date("") {}

    Passenger(int i, string n, string f, string s, string d, string dt)
        : id(i), name(n), flight(f), seat(s), destination(d), date(dt) {}

    void displayTicket() const {
        cout << "\n========== BOARDING PASS ==========\n";
        cout << " Ticket ID   : " << id         << "\n";
        cout << " Passenger   : " << name        << "\n";
        cout << " Flight No   : " << flight      << "\n";
        cout << " Destination : " << destination << "\n";
        cout << " Seat        : " << seat        << "\n";
        cout << " Date        : " << date        << "\n";
        cout << "===================================\n";
    }
};

// File I/O: save one booking record
void saveToFile(const Passenger& p) {
    ofstream file("bookings.txt", ios::app);
    if (file.is_open()) {
        file << p.id << "|" << p.name << "|" << p.flight << "|"
             << p.seat << "|" << p.destination << "|" << p.date << "\n";
        file.close();
    }
}

// File I/O: view all stored bookings
void viewAllBookings() {
    ifstream file("bookings.txt");
    if (!file.is_open()) { cout << " No bookings found.\n"; return; }

    string line;
    bool found = false;
    cout << "\n--- All Bookings ---\n";
    cout << left << setw(6)  << "ID"
              << setw(16) << "Name"
              << setw(10) << "Flight"
              << setw(8)  << "Seat"
              << setw(14) << "Destination"
              << setw(12) << "Date" << "\n";
    cout << string(66, '-') << "\n";

    while (getline(file, line)) {
        found = true;
        string fields[6]; int idx = 0;
        for (char c : line) {
            if (c == '|') idx++;
            else fields[idx] += c;
        }
        cout << left << setw(6)  << fields[0]
                  << setw(16) << fields[1]
                  << setw(10) << fields[2]
                  << setw(8)  << fields[3]
                  << setw(14) << fields[4]
                  << setw(12) << fields[5] << "\n";
    }
    if (!found) cout << " No records available.\n";
    file.close();
}

// Generate next ticket ID from file
int getNextID() {
    ifstream file("bookings.txt");
    int count = 1;
    string line;
    while (getline(file, line)) count++;
    file.close();
    return count;
}

// Seat selection simulation
string selectSeat() {
    string rows[] = {"A", "B", "C", "D", "E"};
    int col;
    cout << " Row (1-10): "; int row; cin >> row;
    if (row < 1 || row > 10) row = 1;
    cout << " Column (1=Window, 2=Middle, 3=Aisle): "; cin >> col;
    if (col < 1 || col > 3) col = 1;
    return rows[col - 1] + to_string(row);
}

// Book a new flight
void bookFlight() {
    string name, flight, destination, date;
    cout << "\n--- Book Flight ---\n";
    cout << " Passenger Name  : "; cin.ignore(); getline(cin, name);
    cout << " Flight Number   : "; getline(cin, flight);
    cout << " Destination     : "; getline(cin, destination);
    cout << " Travel Date     : "; getline(cin, date);
    cout << " Select Seat:\n";
    string seat = selectSeat();

    int id = getNextID();
    Passenger p(id, name, flight, seat, destination, date);
    saveToFile(p);
    p.displayTicket();
    cout << " Booking confirmed successfully!\n";
}

int main() {
    int choice;
    cout << "====================================\n";
    cout << "    SKYLINE AIR RESERVATION SYSTEM  \n";
    cout << "====================================\n";

    do {
        cout << "\n [1] Book a Flight\n";
        cout << " [2] View All Bookings\n";
        cout << " [3] Exit\n";
        cout << " Enter choice: "; cin >> choice;

        switch (choice) {
            case 1: bookFlight();      break;
            case 2: viewAllBookings(); break;
            case 3: cout << " Thank you for using Skyline Air!\n"; break;
            default: cout << " Invalid option. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
