#include "LoginSignup.h"
#include "Menu.h"
#include<iostream>
using namespace std;

int main() {
    LoginSignup obj;  // Object of Login Signin
    Menu menu_obj;  // Object of menu
    obj.LoginSignupDsiplay();  // Display main Login/Signup window
    if (obj.login_successfull) {  // Run menu if Login/Signup was successful
        menu_obj.MenuDisplay();
    }
}
