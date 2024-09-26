//
//  main.cpp
//  Program One Seating Chart
//
//  Brian Klumpp
//  CS 250
//
//  Last edited: 09/25/2024
//
// This program will assign passangers seats on an airplane and display the chart using
// functions, exceptions and vectors.


#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Function that shows the seating chart
void displaySeatingChart(const vector<vector<bool>>& seatingChart) {
    cout << "Seating Chart:\n";
    cout << "    A   B   C   D\n";

    for (size_t row = 0; row < seatingChart.size(); ++row) {
        cout << "Row " << row + 1 << ": "; // Row label
        
        for (size_t seat = 0; seat < seatingChart[row].size(); ++seat) {
            cout << (seatingChart[row][seat] ? " X " : " 0 "); // X if taken, 0 if free
        }
        cout << endl;
    }
}

// Function that allows you to choose your seat
void pickSeat(vector<vector<bool>>& seatingChart, vector<string>& seatsTaken, int row, int seat) {
    if (seatingChart[row][seat]) {
        throw runtime_error("Seat is already taken.");
    }
    
    seatingChart[row][seat] = true;
    seatsTaken.push_back("Row " + to_string(row + 1) + ", Seat " + char('A' + seat));
}

int main() {
    const int totalRows = 5;
    const int seatsInRow = 4;
    
    // Creates the seating chart with no taken seats
    vector<vector<bool>> seatingChart(totalRows, vector<bool>(seatsInRow, false));
    vector<string> seatsTaken;
    
    displaySeatingChart(seatingChart);
    
    while (true) {
        char choice;
        cout << "Assign a seat? (y/n): ";
        cin >> choice;
        
        if (choice == 'n') break;
        
        int row;
        char seatChar;
        cout << "Enter row (1-" << totalRows << ") and seat (A-D): ";
        cin >> row >> seatChar;
        
        // Converts seat character
        int seat = seatChar - 'A';
        
        // Checks if input is valid or invalid
        if (row < 1 || row > totalRows || seat < 0 || seat >= seatsInRow) {
            cout << "Error: Invalid row or seat number." << endl;
            continue;
        }
        
        try {
            pickSeat(seatingChart, seatsTaken, row - 1, seat);
            
            displaySeatingChart(seatingChart);
            
            // Shows what seat re avaialble if not then outputs error message
            cout << "Seats available: " << (totalRows * seatsInRow - seatsTaken.size()) << endl;
        } catch (const runtime_error&) {
            cout << "Error: Seat is already taken." << endl;
        }
    }
    
    // Show the final seating chart
    cout << "Final Seating Chart:\n";
    displaySeatingChart(seatingChart);
    cout << "Seats taken:\n";
    
    for (const auto& seat : seatsTaken) {
        cout << seat << endl;
    
}

    return 0;
}
