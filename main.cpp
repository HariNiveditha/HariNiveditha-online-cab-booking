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
            if(username==u && password==p){
                return true;
            else
            return false;
            }
        }
        //to use the username outside the class
        string getUsername() {
            return username;
        } 
};
int main() {
    cout << "Welcome to Online Cab Booking System!" << endl;
    return 0;
}