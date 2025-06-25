#include <iostream>
#include <string>
#include "Dashboard.h"

void header() { //Display header
    cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n";
    cout << "Semester 3 2024\n";
    cout << "AUCTION APPLICATION\n\n";
    cout << "Instructor: Dr Ling Huo Chong\n";
    cout << "Group: 6\n";
    cout << "Trinh Chi Quang, s3881227\n";
    cout << "Vu Nguyen Nhu Phong, s3879523\n";
    cout << "La Minh Thuan, s3877847\n";
    cout << "Nguyen Thong Linh, s3937160\n\n";
}

char appUse() {
    //Display choices
    string choice;
    cout << "Use the app as 1. Guest    2. Member   3. Admin    4. Exit\n";
    cout << "You can choose 2 to register!\n\n";

    //Ask for choice
    cout << "Enter your choice: ";
    getline(cin, choice);

    while(choice[0] < '1' || choice[0] > '4' || choice.size() > 1) { //Keep asking for valid choice
        cout << "Enter your choice again: ";
        getline(cin, choice);
    }

    return choice[0];
}

void Guest_View() {
    cout << "\nView as Guest\n";
    cout << "You must register or login to view more information!\n";
    cout << "-------------------------------\n";
    cout << std::left << std::setw(5) << "No." 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(150) << "Description"<< endl;
}

char Register_Menu() {
    //display choices
    string choice;
    cout << "Account not found!\n";
    cout << "Do you want to view as Guest or register a new account?\n";
    cout << "1. View as guest\n";
    cout << "2. Register new account\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    getline(cin, choice);

    //Check user selection
    while (choice[0] < '1' || choice[0] > '3' || choice.size() > 1) {
        cout << "Wrong input. Please re-enter your choice (1 or 2): ";
        getline(cin, choice);
    }

    return choice[0];
}

void ItemListing_Template() {
    cout << "Account active item listings\n";
    cout << "-------------------------------\n";
    cout << std::left << std::setw(5) << "No." 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(15) << "Current bid" 
        << std::setw(25) << "Current bidder" 
        << std::setw(25) << "End Date & Time" << endl;
}

void ActiveBid_Template() {
    cout << "Account active bids\n";
    cout << "-------------------------------\n";
    cout << std::left << std::setw(5) << "No." 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(15) << "Account bid" 
        << std::setw(25) << "Current bid" 
        << std::setw(25) << "Seller"
        << std::setw(25) << "End Date & Time" << endl;
}

char accountMenu() {
    //Instructions
    cout << "Menu:\n";
    cout << "1. View Information\n";
    cout << "2. Create bid\n";
    cout << "3. Listing available bids\n";
    cout << "4. Search tool\n";
    cout << "5. Remove bid\n";
    cout << "6. Edit bid\n";
    cout << "7. Rating buyers and/or sellers\n";
    cout << "8. Exit\n";
    
    //Prompt user to choose
    string choice;
    cout << "Enter your choice: ";
    getline(cin, choice);

    //Check the input
    while (choice[0] < '1' || choice[0] > '8' || choice.size() > 1) {
        cout << "Wrong input!\n";
        cout << "Menu:\n";
        cout << "1. View Information\n";
        cout << "2. Create bid\n";
        cout << "3. Listing avaiable bids\n";
        cout << "4. Search tool\n";
        cout << "5. Remove bid\n";
        cout << "6. Edit bid\n";
        cout << "7. Rating buyers and/or sellers\n";
        cout << "8. Exit\n";
        cout << "Enter again: ";
        getline(cin, choice);
    }

    return choice[0];
}

char viewItem_Menu() {
    cout << "\nMenu:\n";
    cout << "1. Bid\n";
    cout << "2. Exit\n";
    
    //Prompt user to choose
    string choice;
    cout << "Enter your choice: ";
    getline(cin, choice);

    //Check the input
    while (choice[0] < '1' || choice[0] > '2' || choice.size() > 1) {
        cout << "Wrong input!\n\n";
        cout << "Menu:\n";
        cout << "1. Bid\n";
        cout << "2. Exit\n";
        cout << "Enter again: ";
        getline(cin, choice);
    }

    return choice[0];
}

char adminMenu() {
    cout << "\nView as Admin\n";
    string choice;
    cout << "1. View members\n";
    cout << "2. Items Listing\n";
    cout << "3. Exit\n";
    cout <<"Enter your choice: ";
    getline(cin, choice);

    while (choice[0] < '1' || choice[0] > '3' || choice.size() > 1) {
        cout << "Invalid choice!. Enter again: ";
        getline(cin, choice);
    }

    return choice[0];
}

short search_Menu(){
    string searchChoice;
    cout << "\nSearch tool\n";
    cout << "Menu:\n";
    cout << "1. Item's name\n";
    cout << "2. Category\n";
    cout << "3. Credict point range \n";
    cout << "4. Exit\n";
                
    //Prompt user to choose
    
    cout << "Enter your choice: ";
    getline(cin,searchChoice);
    

    //Check the input
    while (searchChoice[0] < '1' || searchChoice[0] > '4' && searchChoice.length() != 1) {
        cout << "Wrong input!\n";
        cout << "Menu:\n";
        cout << "1. Iteam's name\n";
        cout << "2. Category\n";
        cout << "3. Credict point range \n";
        cout << "4. Exit\n";
        cout << "Enter your choice again: ";
        getline(cin,searchChoice);
    }

    return (searchChoice[0] - 48);
}

short search_Charac_Menu(){
    string searchCtChoice;
    cout << "Menu:\n";
    cout << "1. search\n";
    cout << "2. exit\n";
    
    cout << "Enter your choice: ";
    getline(cin, searchCtChoice);
        
    while (searchCtChoice[0] < '1' || searchCtChoice[0] > '2' && searchCtChoice.length() != 1) {
        cout << "Wrong input!, please input again:\n";
        cout << "Menu:\n";
        cout << "1. search\n";
        cout << "2. exit\n";
        cout << "Enter your choice: ";
        getline(cin, searchCtChoice);
    }

    return (searchCtChoice[0] - 48);
}

short rating_Menu(){
    string ratingChoice;
    cout << "Menu:\n";
    cout << "1. Rate sellers\n";
    cout << "2. Rate buyers\n";
    cout << "3. Exit\n";
    
    cout << "Enter your choice: ";
    getline(cin, ratingChoice);
        
    while (ratingChoice[0] < '1' || ratingChoice[0] > '3' && ratingChoice.length() != 1) {
        cout << "Wrong input!, please input again:\n";
        cout << "Menu:\n";
        cout << "1. Rate sellers\n";
        cout << "2. Rate buyers\n";
        cout << "3. Exit\n";
        getline(cin, ratingChoice);
    }

    return (ratingChoice[0] - 48);
}