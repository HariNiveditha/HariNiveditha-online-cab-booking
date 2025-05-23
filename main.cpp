#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
using namespace std;

class user {
private:
    string username, password;
public:
    void setData(string u, string p) {
        username = u;
        password = p;
    }

    bool checkCredentials(string u, string p) {
        return username == u && password == p;
    }

    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }
};

class cab {
public:
    static void displayCabOptions() {
        cout << "\nChoose a cab type:\n";
        cout << "1. Bike  (Rs 10/km)\n";
        cout << "2. Auto (Rs 15/km)\n";
        cout << "3. Car (Rs 20/km)\n";
    }

    static float getRate(const string& cabType) {
        if (cabType == "Bike") return 10;
        if (cabType == "Auto") return 15;
        if (cabType == "Car") return 20;
        return 0;
    }
};

class booking {
private:
    string username, cabType, driverName;
    int rating;
    float distance, fare;
    bool cancelled = false;

public:
    booking(string user, string type, float dist, string driver) {
        username = user;
        cabType = type;
        distance = dist;
        fare = cab::getRate(type) * dist;
        driverName = driver;
        rating = -1;
    }

    void cancelBooking() {
        cancelled = true;
        cout << "Booking has been cancelled.\n";
    }

    void giveRating(int r) {
        if (r >= 1 && r <= 5) {
            this->rating = r;
            cout << "Thank you for rating your ride " << rating << " star(s)!\n";
        } else {
            cout << "Invalid rating. Please give between 1 and 5.\n";
        }
    }

    void displayBooking() {
        if (cancelled) {
            cout << "Booking has been cancelled\n";
        } else {
            cout << "Booking confirmed\n";
            cout << "User: " << username << endl;
            cout << "Cab Type: " << cabType << endl;
            cout << "Distance: " << distance << " km\n";
            cout << "Fare: Rs " << fare << endl;
            cout << "Driver: " << driverName << endl;
            if (rating == -1) {
                cout << "Please rate the ride\n";
            } else {
                cout << "Ride Rating: " << rating << " star(s)\n";
            }
        }
    }

    bool iscancelled() {
        return cancelled;
    }

    string getDriver() {
        return driverName;
    }
};

class userLogin {
private:
    vector<user> users;
    user currentUser;
    bool isLogged = false;
    vector<booking> rideHistory;
    queue<string> driverQueue;

public:
    void addUser() {
        string u, p;
        cout << "Enter new username: ";
        cin >> u;
        cout << "Enter new password: ";
        cin >> p;
        user newUser;
        newUser.setData(u, p);
        users.push_back(newUser);
        saveUsersToFile();
        cout << "Registered successfully\n";
        currentUser = newUser;
        isLogged = true;
    }

    void initializeDrivers() {
        driverQueue.push("Driver1\nCab Number: TS 09 EB 4811");
        driverQueue.push("Driver2\nCab Number: TS 03 MF 9999");
        driverQueue.push("Driver3\nCab Number: TS 11 EQ 2007");
        driverQueue.push("Driver4\nCab Number: TS 08 EG 0000");
        driverQueue.push("Driver5\nCab Number: TS 09 MF 5632");
    }

    bool isDriverAvailable() {
        return !driverQueue.empty();
    }

    string assignDriver() {
        if (!driverQueue.empty()) {
            string driver = driverQueue.front();
            driverQueue.pop();
            return driver;
        }
        return "NoDriver";
    }

    void returnDriver(string driver) {
        driverQueue.push(driver);
    }

    void loadUsersFromFile() {
        ifstream inFile("users.txt");
        string u, p;
        while (inFile >> u >> p) {
            user newUser;
            newUser.setData(u, p);
            users.push_back(newUser);
        }
        inFile.close();
    }

    void saveUsersToFile() {
        ofstream outFile("users.txt");
        for (auto& user : users) {
            outFile << user.getUsername() << " " << user.getPassword() << endl;
        }
        outFile.close();
    }

    void loginUser() {
        string u, p;
        bool existing = false;
        cout << "Enter the username: ";
        cin >> u;
        cout << "Enter the password: ";
        cin >> p;
        for (auto& user : users) {
            if (user.checkCredentials(u, p)) {
                cout << "Login successful\n";
                currentUser = user;
                isLogged = true;
                existing = true;
                break;
            }
        }
        if (!existing)
            cout << "Invalid credentials\n";
    }

    void logoutUser() {
        isLogged = false;
        cout << "Log out successful\n";
    }

    bool loginStatus() {
        return isLogged;
    }

    user getCurrentUser() {
        return currentUser;
    }

    void addRide(booking b) {
        rideHistory.push_back(b);
    }

    void viewRideHistory() {
        if (rideHistory.empty()) {
            cout << "No rides found.\n";
            return;
        }
        cout << "\nRide History:\n";
        for (int i = 0; i < rideHistory.size(); i++) {
            cout << "\nRide " << i + 1 << ":\n";
            rideHistory[i].displayBooking();
        }
    }

    void cancelLastRide() {
        if (!rideHistory.empty()) {
            rideHistory.back().cancelBooking();
            returnDriver(rideHistory.back().getDriver());
        } else {
            cout << "No booking to cancel.\n";
        }
    }

    void rateLastRide() {
        if (rideHistory.empty()) {
            cout << "No rides to rate.\n";
            return;
        }
        if (rideHistory.back().iscancelled()) {
            cout << "Cannot rate a cancelled ride.\n";
            return;
        }
        int r;
        cout << "Enter your ride rating (1-5 stars): ";
        cin >> r;
        rideHistory.back().giveRating(r);
        returnDriver(rideHistory.back().getDriver());
    }
};

int main() {
    userLogin userSystem;
    userSystem.loadUsersFromFile();
    userSystem.initializeDrivers();

    int choice;
    char cancelChoice;

    cout << "Welcome to the Online Cab Booking System\n";

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            userSystem.addUser();
        } else if (choice == 2) {
            userSystem.loginUser();
        } else if (choice == 3) {
            cout << "Thank you for using the system!\n";
            break;
        } else {
            cout << "Invalid option. Try again.\n";
        }

        while (userSystem.loginStatus()) {
            int subChoice;
            cout << "\n1. Book a Cab\n2. Cancel the ride\n3. View Ride History\n4. Rate Last Ride\n5. Logout\nEnter your choice: ";
            cin >> subChoice;

            if (subChoice == 1) {
                string cabType;
                int cabChoice;
                float distance;

                cab::displayCabOptions();
                cout << "Enter your cab choice (1/2/3): ";
                cin >> cabChoice;

                if (cabChoice == 1) cabType = "Bike";
                else if (cabChoice == 2) cabType = "Auto";
                else if (cabChoice == 3) cabType = "Car";
                else {
                    cout << "Invalid cab choice.\n";
                    continue;
                }

                cout << "Enter distance (in km): ";
                cin >> distance;

                if (!userSystem.isDriverAvailable()) {
                    cout << "No drivers available at the moment. Try again later.\n";
                    continue;
                }

                string assignedDriver = userSystem.assignDriver();
                booking b(userSystem.getCurrentUser().getUsername(), cabType, distance, assignedDriver);

                cout << "Assigned Driver: " << assignedDriver << endl;
                b.displayBooking();

                int rideRating;
                cout << "Please rate your ride (1-5 stars): ";
                cin >> rideRating;
                b.giveRating(rideRating);

                userSystem.addRide(b);
            } else if (subChoice == 2) {
                cout << "Do you want to cancel booking? (y/n): ";
                cin >> cancelChoice;
                if (cancelChoice == 'y' || cancelChoice == 'Y') {
                    userSystem.cancelLastRide();
                }
            } else if (subChoice == 3) {
                userSystem.viewRideHistory();
            } else if (subChoice == 4) {
                userSystem.rateLastRide();
            } else if (subChoice == 5) {
                userSystem.logoutUser();
                cout << endl;
            } else {
                cout << "Invalid option.\n";
            }
        }
    }

    return 0;
}
