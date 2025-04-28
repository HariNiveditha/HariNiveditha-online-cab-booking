#include<iostream>
#include<vector>
#include<string>
using namespace std;
 
class user{
    private:
         string username,password;
    public:
    //to set the data of the user
        void setData(string u,string p){
            username=u;
            password=p;
        }
    //to check if the input credentials match the stored credentials
        bool checkCredentials(string u,string p){
            if(username==u && password==p)
                return true;
            else
                return false;
            
        }
        //to use the username outside the class
        string getUsername() {
            return username;
        } 
};

class userLogin{
    private:
        vector<user> users;
        user currentUser;
        bool isLogged = false;
    public:
    void addUser(){
        string u,p;
        cout<<"Enter new username: ";
        cin>>u;
        cout<<"Enter new password: ";
        cin>>p;
        user newUser;
        newUser.setData(u,p);
        users.push_back(newUser);
        cout<<"Registered successfully"<<endl;
        currentUser = newUser;
        isLogged = true;
    }
    
        void loginUser(){
            string u,p;
            bool existing = false;
            cout<<"Enter the username: ";
            cin>>u;
            cout<<"Enter the password: ";
            cin>>p;
            for(auto &user : users){
                if(user.checkCredentials(u,p)){
                    cout<<"Login successful"<<endl;
                    currentUser = user;
                    isLogged = true;
                    existing = true;
                    break;
                }
            }
            if(!existing)
                cout<<"Invalid credentials"<<endl;
        }
        void logoutUser(){
            isLogged = false;
            cout<<"Log out successful";
        }
        bool loginStatus(){
            return isLogged;
        }
        user getCurrentUser(){
            return currentUser;
        }
};

class cab{
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

class booking{
    private:
        string username, cabType;
        float distance, fare;
    public:
        booking(string user, string type, float dist) {
        username = user;
        cabType = type;
        distance = dist;
        fare = cab::getRate(type) * dist;
    }
    void displayBooking() {
        cout<<"Booking confirmed"<<endl;
        cout << "User: " << username << endl;
        cout << "Cab Type: " << cabType << endl;
        cout << "Distance: " << distance << " km\n";
        cout << "Fare: ₹" << fare << endl;
    }
};

int main() {
    userLogin userSystem;
    int choice;
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
            if (userSystem.loginStatus()) {
                // If login successful, allow cab booking
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

                booking b(userSystem.getCurrentUser().getUsername(), cabType, distance);
                b.displayBooking();

                userSystem.logoutUser(); // Logout after booking
            }
        }
        else if (choice == 2) {
            userSystem.loginUser();
            if (userSystem.loginStatus()) {
                // If login successful, allow cab booking
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

                booking b(userSystem.getCurrentUser().getUsername(), cabType, distance);
                b.displayBooking();

                userSystem.logoutUser(); // Logout after booking
            }
        }
        else if (choice == 3) {
            cout << "Thank you for using the system!\n";
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
