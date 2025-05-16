#pragma once
#include<iostream>
#include<sstream>  // For using stringstream
using namespace std;

class TrainTimings {
protected:
    int searched_train_no[10];  // Stores train numbers of user searched trains
    bool trains_found;
public:
    TrainTimings() {
        for (int i=0 ; i<=9 ; i++) {
            searched_train_no[i] = 0;
        }
        trains_found = false;
    }
    void GetTrainTimings() {
        string user_departure , user_destination;
        cout<<"\nEnter Your Departure City : ";
        cin>>user_departure;
        cout<<"\nEnter Your Destination : ";
        cin>>user_destination;
        for (int i=0 ; i<user_departure.length() ; i++) {  // Loop to convert user_departure to lowercase
            user_departure[i] = tolower(user_departure[i]);
        }
        for (int i=0 ; i<user_destination.length() ; i++) {  // Loop to convert user_destination to lowercase
            user_destination[i] = tolower(user_destination[i]);
        }
        trains_found = false;
        string line;  // For storing each line from TrainTimings.txt file temporarily
        ifstream file("TrainTimings.txt");
        if (!file) {  // If error in opening TrainTimings.txt file
            cout<<"\nError Connecting Exiting The Program";
            exit(1);
        }
        int i = 0;  // Counter for searched_train_no array
        cout<<"\n\t\t\tTrains Available\n";

        while (getline(file,line)) {  // For reading line by line records of TrainTimings.txt file
            stringstream ss(line);  // Takes line in buffer and will help in breaking line into words
            int train_no;  // For storing train number from TrainTimings.txt file
            string departure, destination ,time , train_name , price;  // For storing departures , destinations , time , trainname & price from TrainTimings.txt file
            ss>>train_no>>departure>>destination>>time>>train_name>>price;  // Stores each word in each variable from each line of TrainTimings.txt

            if ((destination == user_destination) && (departure == user_departure)) {  // For checking if departure & destination found
                cout<<"\nTrain No : "<<train_no<<" , From : "<<departure
                <<" , To : "<<destination<<" , Time : "<<time<<" hrs"
                <<" , Train Name : "<<train_name<<" , Price : "<<price<<" Rs"<<endl;  // Displays complete one record
                searched_train_no[i] = train_no;
                i++;  // Store train no of searched trains that will be useful in bookings
                trains_found = true;
            }
        }
        file.close();
        if (!trains_found) {  // If no train is found
            cout<<"\nNo Trains Found At Your Entered Places.....";
            Sleep(1500);
        }
        else {
            Sleep(1500);  // It is in else block to avoid sleep multiple times when no train found
        }
    }
};
