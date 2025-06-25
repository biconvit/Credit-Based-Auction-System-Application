#include <iostream>
#include "Admin.h"

//test
LoginAdmin::LoginAdmin() : Login("admin", "1234") {}

// bool LoginAdmin::checkUsername(string username){
//     if (username == getUsername())
//         return true;
//     else 
//         return false;
// }

bool LoginAdmin::checkUsername(string &username) {
    while(username != getUsername()) {
        cout << "Incorrect! Enter admin account again (\"Exit\" to exit): ";
        getline(cin, username);

        if(username == "Exit")
            return false;
    }
    return true;
}

bool LoginAdmin::checkPassword(string &password){
    while(password != getPwd()) {
        cout << "Incorrect! Enter admin password again: ";
        getline(cin, password);

        if(password == "Exit")
            return false;
    }
    return true;
}