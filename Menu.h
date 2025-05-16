#pragma once
#include "Booking.h"
#include "TrainTimings.h"
#include<iostream>
using namespace std;

class Menu : public Booking , virtual public TrainTimings {
    int menu_choice;
public:
    Menu() {
        menu_choice = 0;
    }
    void MenuDisplay() {
        cout<<"\n\n\t---------- Railway Booking System ----------\n\n";
        do {  // Loop for executing menu again & again
            cout<<"\n\n\t\t\t    Menu\n";
            cout<<"\n1 - Book A Ticket ";
            cout<<"\n2 - View Your Bookings ";
            cout<<"\n3 - See Train Timings ";
            cout<<"\n4 - Exit \n";
            do {  // Loop for getting correct user choice
                cout<<"\nEnter Your Choice : ";
                while(!(cin>>menu_choice)) {
                    cout<<"\nInvalid Entry Do Again.....";
                    cout<<"\nEnter Your Choice : ";
                    cin.clear();
                    cin.ignore(123,'\n');
                }
                if ((menu_choice >= 1) && (menu_choice <= 4)) {
                    break;
                }
                else {
                    cout<<"\nInvalid Entry Do Again.....";
                }
            } while (true);
            if (menu_choice == 4) {  // Break loop & end program 
                break;
            }
            else if (menu_choice == 1) {  // If user want's to book ticket
                j = 0;  // Reseting booking counter to 0
                BookTicket();
            }
            else if (menu_choice == 2) {  // If user want's to see bookings
                SeeBookings();
            }
            else if (menu_choice == 3) {  // If user want's to see train scedule
                cout<<"\n\t\t\t  Train Timings\n";
                GetTrainTimings();
            }
        } while(true);
    }
};