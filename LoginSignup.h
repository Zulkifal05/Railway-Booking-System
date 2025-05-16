#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>  //For using Sleep function
using namespace std;

class LoginSignup {
protected:
    string password, CNIC;
    int LoginSignup_choice;
public:
    bool login_successfull;  // For tracking of successful login
    //Constructor
    LoginSignup() {
        CNIC = password = "";
        login_successfull = false;
    }

    // Function for main Login/Signup display
    void LoginSignupDsiplay() {  
        cout<<"\n\t---------- Railway Booking System ----------\n\n";
        cout<<"1 - SignUp If You Have No Previous Account\n";
        cout<<"2 - LogIn If You Have Previous Account";
        do {  // Loop for taking Choice of login/Signup
            cout<<"\nEnter Your Choice : ";
            while(!(cin>>LoginSignup_choice)) {  // Loop for input error handling i.e correct data type input
                cout<<"\nInvalid Entry!";
                cout<<"\nEnter Your Choice : ";
                cin.clear();
                cin.ignore(123,'\n');
            }
            if ((LoginSignup_choice == 1) || (LoginSignup_choice == 2)) {
                break;  // Break if the correct input i.e 1 or 2
            }
            else {
                cout<<"\nInvalid Entry!";  // If invalid input i.e not 1 or 2
            }
        } while(true);

        // Call the respective Login/Signup functions as user's choice
        if (LoginSignup_choice == 1) {
            Signup();
        }
        else if (LoginSignup_choice == 2) {
            Login();
        }
    }

    //Function For Signup
    void Signup() {
        string line;
        cout<<"\n\t\t\tSign Up\n";
        do {
            bool user_already_exist = false;  // Checks wheather a CNIC already exists
            cout<<"\nEnter Your CNIC (Without spaces & '-') : ";
            cin>>CNIC;
            cout<<"\nEnter Your Password (Be careful while entering): ";           
            cin>>password;

            ifstream file ("Users.txt");
            if (!file) {  // If error in opening Users.txt file
                cout<<"\nUnable to signup exiting the program....";
                exit(1);
            }
            while (getline(file,line)) {
                size_t spacePos = line.find(' ');  // Check index of first space
                if (spacePos != string::npos) {
                    string fileCNIC = line.substr(0, spacePos);  // Take only CNIC part from Users.txt
                    if (fileCNIC == CNIC) {  // If CNIC is already signedup
                        user_already_exist = true;
                    }
                }
            }

            if (user_already_exist) {  // If CNIC already exists again take input
                file.close();
                login_successfull = false;
                cout<<"\nUser CNIC Already Exists Do Again.....";
            }
            else {  // Exit the input loop
                file.close();
                // Now write the data to Users.txt file as verified already
                ofstream file("Users.txt",ios::app);
                if (!file) {  // If unable to open file for writing
                    cout<<"\nUnable to signup exiting the program....";
                    exit(1);
                }
                file<<CNIC<<" "<<password<<"\n";  // Add new user record in new line
                file.close();
                cout<<"\nUser Signedup Successfully";
                login_successfull = true;
                Sleep(1500);  // Pause execustion for 3 seconds
                break;
            }
        } while(true);
    }

    //Function For Login
    void Login() {
        string line;
        int unssuccesful_login = 0;  // For tracking unsuccessful login attempts
        cout<<"\n\t\t\tLog In\n";
        do {  // Loop till login correctly
            bool user_exists = false;  // Checks wheather a CNIC already exists
            cout<<"\nEnter Your CNIC (Without spaces & '-') : ";
            cin>>CNIC;
            cout<<"\nEnter Your Password (Be careful while entering): ";           
            cin>>password;

            ifstream file ("Users.txt");
            if (!file) {  // If error in opening Users.txt file
                cout<<"\nUnable to signup exiting the program....";
                exit(1);
            }
            while (getline(file,line)) {  // Search line by line for record
                size_t spacePos = line.find(' ');  // For index of space as between CNIC & Password in users.txt
                if (spacePos != string::npos) {
                    string fileCNIC = line.substr(0, spacePos);
                    string filePassword = line.substr(spacePos + 1);

                    if ((fileCNIC == CNIC) && (filePassword == password)) {
                        user_exists = true;
                        break;
                    }
                }
            }

            if (user_exists) {  // If CNIC & Password Exist then login successful
                file.close();
                cout<<"\nLogin Successful.....";
                login_successfull = true;
                Sleep(1500);
                break;
            }
            else {  // If CNIC or Password is wrong
                file.close();
                login_successfull = false;
                if (unssuccesful_login == 3) {  // If there are three unsuccessful login attempts
                    cout<<"\nToo Many Unsuccessfull Attempts Exiting Program.....";
                    exit(1);
                }
                else {
                    cout<<"\nInvalid CNIC or Password Do Again.....";
                    unssuccesful_login++;
                }
            }
        } while(true);
    }
};
