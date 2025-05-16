#pragma once
#include "LoginSignup.h"
#include "TrainTimings.h"
#include<iostream>
#include<iomanip>  // For using manipulator
using namespace std;

class Booking : public LoginSignup , virtual public TrainTimings {
protected:
    int book_train_no[10];  // For storing train id's of user's input
    string book_CNIC;  // For storing CNIC of person doing booking
    int j;  // Counter for book_train_no
    string ticket_file;  // For storing file name of ticket generated
public:
    Booking() {
        for (int i=0 ; i<10 ; i++) {
            book_train_no[i] = -1;  // -1 to keep difference from default values of searched_train_no
        }
        j = 0;
        book_CNIC = "";
        ticket_file = "";
    }

    // Function for validating train number
    bool CheckCorrectNo() {  
        for (int i=0 ; i<10 ; i++) {  // For checking if user's input train id matches valid train id's
            if (book_train_no[j] == searched_train_no[i]) {
                return true;
            }
        }
        return false;
    }

    // Function for saving bookings in Bookings.txt
    void SaveBooking() {  
        string line;  // For reading line by line of TrainTimings.txt file
        ifstream file("TrainTimings.txt");
        ofstream write("Bookings.txt",ios::app);
        if ((!file) || (!write)) {
            cout<<"\nError Occured While Saving Exiting Program.....";
            exit(1);
        }
        string word;  // For skiping train id of TrainTimings.txt file
        string train_name , book_departure , book_destination , book_time , price;  // For storing train name , departure , destination , book time  & price of user's input

        while (getline(file,line)) {  // For reading line by line of TrainTimings.txt
            int train_id;  // For getting train id from TrainTimings.txt to get train name of that id
            stringstream ss(line);
            ss>>train_id;
            if (train_id == book_train_no[j]) {  // For writing only those records as user entered train no
                stringstream ss(line);
                ss>>word>>book_departure>>book_destination>>book_time>>train_name>>price;

                write<<book_CNIC<<" "<<book_train_no[j]<<" "
                <<book_departure<<" "<<book_destination
                <<" "<<train_name<<" "<<book_time<<" "<<price<<endl;  // For writing into Bookings.txt file
                GenerateTicket(book_CNIC,to_string(book_train_no[j]),book_departure,book_destination,train_name,book_time,price);  // Call to generate ticket
            }
        }
        file.close();
        write.close();
    }

    // Function for generating ticket
    void GenerateTicket(string b_c, string t_n, string dep, string des, string t_name, string b_t,string prc) {
        ticket_file = "Ticket" + to_string(j+1) + ".txt";
        ofstream write(ticket_file);
        if(!write) {
            cout<<"\nAn Error Occurred While Generating Ticket Exiting Program.....";
            exit(1);
        }
        write<<"\t\t\t\t            |"<<endl
	    <<"              ===== Ticket ====="<<"            |"<<endl<<"\t\t\t\t            |"<<endl
        <<"        CNIC       : "<<setw(15)<<b_c<<"        |"<<endl
        <<"        Train No   : "<<setw(15)<<t_n<<"        |"<<endl
        <<"        From       : "<<setw(15)<<dep<<"        |"<<endl
        <<"        To         : "<<setw(15)<<des<<"        |"<<endl
        <<"        Train Name : "<<setw(15)<<t_name<<"        |"<<endl
        <<"        Train (Hrs): "<<setw(15)<<b_t<<"        |"<<endl
        <<"        Price (Rs) : "<<setw(15)<<prc<<"        |"<<endl
        <<"____________________________________________|";  // Writing on ticket
        write.close();
    }

    // Function for booking ticket
    void BookTicket() {
        cout<<"\n\t\t\tBook A Ticket\n";
        GetTrainTimings();  // Take trains for user
        if (trains_found) {  // If trains were found according to user input
            bool more_choice = 1;  // For storing choice for more bookings
            cout<<"\nEnter Your CNIC (Without Spaces & '-') : ";
            cin>>book_CNIC;
            do {  // For taking correct input
                cout<<"\nEnter Train Number Of Available Trains For Your Booking : ";
                while(!(cin>>book_train_no[j])) {  // For taking correct data type entry
                    cout<<"\nInvalid Entry Do Again.....";
                    cout<<"\nEnter Train Number Of Avaiable Trains For Your Booking : ";
                    cin.clear();
                    cin.ignore(123,'\n');
                }

                if (!CheckCorrectNo()) {
                    cout<<"\nInvalid Entry Do Again.....";
                }
                else {  // If correct train id
                    SaveBooking();  // Saving a booking in Bookings.txt file
                    cout<<"\nBooking Done!";
                    do {
                        cout<<"\nDo You Want To Book More Seats (1/0): ";
                        while (!(cin>>more_choice)) {  // For getting correct choice
                            cout<<"\nInvalid Choice Do Again.....";
                            cout<<"\nDo You Want To Book More Seats (1/0): ";
                            cin.clear();
                            cin.ignore(123,'\n');
                        }
                        if ((more_choice != 1) && (more_choice != 0)) {  // If choice is not valid i.e 1/0
                            cout<<"\nInvalid Entry Do Again.....";
                        }
                        else if (more_choice == 1) {  // If choice is valid but 1
                            j++;
                            break;
                        }
                    } while(more_choice);  // Loop exits when choice for more is 0
                }
            } while(more_choice);  // Loop exits when choice for more is 0
        }
    }

    // Function for seeing bookings
    void SeeBookings() {
        cout<<"\n\t\t\t Your Bookings\n";
        cout<<"\nEnter Your CNIC (Without Spaces & '-') : ";
        cin>>book_CNIC;
        bool book_found = false;  // For tracking if CNIC's bookings found
        ifstream file("Bookings.txt");
        string line;  // For reading line by line
        if (!file) {
            cout<<"\nError Occured While Saving Exiting Program.....";
            exit(1);
        }
        else {  // If Bookings.txt file is open & also not empty
            string CNIC_word , train_no , train_name , book_departure , book_destination , book_time , price;  // For checking user's CNIC & other things to display those bookings
            while (getline(file,line)) {
                stringstream ss(line);
                ss>>CNIC_word>>train_no>>book_departure>>book_destination>>train_name>>book_time>>price;
                if(CNIC_word == book_CNIC) {  // Display only particular CNIC's bookings
                    cout<<"\nTrain No : "<<train_no<<" , From : "<<book_departure
                    <<"  , To : "<<book_destination<<"  , Train Name : "<<
                    train_name<<"  , Time : "<<book_time<<" Hrs"<<" , Price : "<<price<<" Rs\n";
                    book_found = true;  // If bookings are found for CNIC entered
                }
            }
            file.close();  // Close file after reading
            if (!book_found) {
                cout<<"\nEntered CNIC Has No Bookings.....";
                Sleep(1500);
            }
            else {
                Sleep(1500);  // It is in else block to avoid sleep multiple time when no booking found
            }
        }
    }
};
