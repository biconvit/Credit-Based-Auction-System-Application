#include <iostream>
#include "Member.h"

//Login class
//Constructor
Login::Login(string username = "", string password = "") :
             username(username), password(password) {}

//Getter
string Login::getUsername() {return username;}
string Login::getPwd() {return password;}

//Setter
void Login::setPwd(string password) {this->password = password;} 
//Display
string Login::display() {return username + "-" + password + "\n";}



//MemberInfo class
//Assume the ID type is citizen ID
//Constructor
MemberInfo::MemberInfo(string fullName = "", string phoneNumber = "", string email = "",
        string ID_type = "1", string ID = "", int CP = 0, double buyer_rating_score = 3.0, double seller_rating_score = 3.0, int number_rated_buyer = 1, int number_rated_seller = 1) 
        : fullName(fullName), phoneNumber(phoneNumber), email(email), ID_type(ID_type), ID(ID), CP(CP), buyer_rating_score(buyer_rating_score), 
        seller_rating_score(seller_rating_score), number_rated_buyer(number_rated_buyer), number_rated_seller(number_rated_seller) {}

//Getter
int MemberInfo::getCP() {return CP;}
double MemberInfo::getBuyerRating() {return buyer_rating_score;}
double MemberInfo::getSellerRating() {return seller_rating_score;}

//Setter
void MemberInfo::setFullName(string fullName) {this->fullName = fullName;}
void MemberInfo::setPhoneNum(string phoneNumber) {this->phoneNumber = phoneNumber;}
void MemberInfo::setEmail(string email) {this->email = email;}
void MemberInfo::setID_type(string ID_type) {this->ID_type = ID_type;}
void MemberInfo::setID(string ID) {this->ID = ID;}
void MemberInfo::setCP(int CP) {this->CP += CP;}
void MemberInfo::setBuyerRating(int buyer_rating_score) {
        //Calculate average rating score
        this->buyer_rating_score = (this->buyer_rating_score*number_rated_buyer + buyer_rating_score) / (number_rated_buyer+1);
        number_rated_buyer++;
}
void MemberInfo::setSellerRating(int seller_rating_score) {
        //Calculate average rating score
        this->seller_rating_score = (this->seller_rating_score*number_rated_seller + seller_rating_score) / (number_rated_seller+1);
        number_rated_seller++;
}

//Display
string MemberInfo::display() {return fullName + "-" + phoneNumber + "-" + email + "-" + ID_type + "-" + ID + "-" + std::to_string(CP) 
                                                + "-" + std::to_string(buyer_rating_score) + "-" + std::to_string(number_rated_buyer)  
                                                + "-" + std::to_string(seller_rating_score) + "-" + std::to_string(number_rated_seller) + "\n";}
void MemberInfo::terminalDisplay() {
        cout << "Full name: " << fullName << endl;
        cout << "Phone number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        if(ID_type == "1") cout << "ID type: Citizen ID\n";
        else if(ID_type == "2") cout << "ID type: Passport\n";
        cout << "ID: " << ID << endl;
        cout << "CP: " << CP << endl;
        cout << "Buyer rating score: " << buyer_rating_score << endl;
        cout << "Number of rated as Buyer: " << number_rated_buyer << endl;
        cout << "Seller rating score: " << seller_rating_score << endl;
        cout << "Number of rated as Seller: " << number_rated_seller << endl;
}



//LoginSystem class
//Constructor
LoginSystem::LoginSystem(vector<Login> loginInfos, vector<MemberInfo> memberInfos)
                         : loginInfos(loginInfos), memberInfos(memberInfos) {}

//Load Login Data
void LoginSystem::loadLoginData() {
        //Check whether file exist. If not, create a new one
        tryOpenFile(LOGINFILE);

        //Load Login Info
        fstream logindata;

        //Try to open file to read
        logindata.open(LOGINFILE, std::ios::in);
        //Check whether file is opened
        if(!logindata) {
                cerr << "Failed to open file!\n";
                return;
        }
        
        //Temporary variables to save login info
        string username;
        string pwd;

        //Get data from Login file
        while(logindata.peek() != EOF) {
                getline(logindata, username, '-');
                getline(logindata, pwd, '\n');

                //push back login data
                loginInfos.push_back(Login(username, pwd));
        }

        logindata.close();
}

void LoginSystem::saveLoginData() {
        fstream logindata;
        
        //Try to open file to write
        logindata.open(LOGINFILE, std::ios::out);
        //Check whether file is opened
        if(!logindata) {
                cerr << "Failed to open file!\n";
                return;
        }

        for(Login &i : loginInfos) logindata << i.display();

        logindata.close();

        cout << "Login Infos are saved!\n";
}

void LoginSystem::loadMemberData() {
        //Check whether file exist. If not, create a new one
        tryOpenFile(MEMBERFILE);

        //Load Login Info
        fstream memberdata;

        //Try to open file to read
        memberdata.open(MEMBERFILE, std::ios::in);
        //Check whether file is opened
        if(!memberdata) {
                cerr << "Failed to open file!\n";
                return;
        }
        
        //Temporary variables to save login info
        string fullName;
        string phoneNumber;
        string email;
        string ID_type;
        string ID;
        string CP;
        string buyer_rating_score;
        string seller_rating_score;
        string number_rated_buyer;
        string number_rated_seller;
        //Get data from Login file
        while(memberdata.peek() != EOF) {
                getline(memberdata, fullName, '-');
                getline(memberdata, phoneNumber, '-');
                getline(memberdata, email, '-');
                getline(memberdata, ID_type, '-');
                getline(memberdata, ID, '-');
                getline(memberdata,CP,'-');
                getline(memberdata, buyer_rating_score, '-');
                getline(memberdata, number_rated_buyer, '-');
                getline(memberdata, seller_rating_score, '-');
                getline(memberdata, number_rated_seller, '\n');
                //push back login data
                memberInfos.push_back(MemberInfo(fullName, phoneNumber, email, ID_type, ID, std::stoi(CP), std::stod(buyer_rating_score), 
                                std::stod(seller_rating_score), std::stoi(number_rated_buyer), std::stoi(number_rated_seller)));
        }

        memberdata.close();
}

void LoginSystem::saveMemberData() {
        fstream memberdata;
        
        //Try to open file to write
        memberdata.open(MEMBERFILE, std::ios::out);
        //Check whether file is opened
        if(!memberdata) {
                cerr << "Failed to open file!\n";
                return;
        }

        for(MemberInfo &i : memberInfos) memberdata << i.display();

        memberdata.close();

        cout << "Member Infos are saved!\n";
}

int LoginSystem::findUser(string username) {
        for(int i = 0; i < loginInfos.size(); i++) { //Find user based on username
                if(username == loginInfos[i].getUsername()) return i;
        }

        return -1;
}

void LoginSystem::registerUser(string username) {
        string pwd;
        cout << "Enter new password to register: ";
        getline(cin,pwd);
        
        //Check whether the password is a strong password
        while(!isWeakPwd(pwd)) {
                cout << "Please enter again: ";
                getline(cin, pwd);
        }

        //After checking, saving username and password
        cout << "Your password is strong\n";
        loginInfos.push_back(Login(username,pwd));
        
        //Ask for personal information
        cout << "Please provide your persional information: \n";
        // temporary varaiable to store user's input data             
        string InfullName, InphoneNumber, Inemail, InID_type, InID; // CP init is 0, rating score init is 3.0;

        //Get user's Full name
        cout << "Enter your full name: "; 
        getline(cin,InfullName);
        //Check whether user's Full name is valid
        while(!isValidName(InfullName)) {
                cout << "Name contains alpha characters only!\n";
                cout << "Enter your name again: ";
                getline(cin, InfullName);
        }

        //Get user's phone number
        cout << "Enter your phone number: "; 
        getline(cin,InphoneNumber);
        //Check whether user's phone number is valid
        while(!isValidPhoneNumber(InphoneNumber)) {
                cout << "Phone number contains numbers only!\n";
                cout << "Enter your phone number again: ";
                getline(cin, InphoneNumber);
        } 

        //Get user's email
        cout << "Enter your email: "; 
        getline(cin,Inemail);
        //Check whether user's email is valid
        while(!isValidEmail(Inemail)) {
                cout << "Invalid email\n";
                cout << "Enter your email again: ";
                getline(cin, Inemail);
        }

        //Get user's ID type
        cout << "Enter your ID type: 1 - Citizen ID or 2 - Passport:  "; 
        getline(cin,InID_type);
        //Check ID type
        while(InID_type != "1" && InID_type != "2") {
                cout << "Invalid ID type!\n";
                cout << "Enter again: ";
                getline(cin,InID_type);
        }

        //Instruction to input ID based on ID type
        if(InID_type == "1") cout << "Contain only number!\n";
        else if(InID_type == "2") cout << "The first letter is an uppercase. The remaining is number!\n";

        //Get user's ID
        cout << "Enter your ID series: "; 
        getline(cin,InID);
        //Check if the ID series match the ID type
        while(!isValidID(InID_type,InID)) { 
                cout << "Your ID series does not match the ID type \n";
                cout << "Enter your ID series again: "; 
                getline(cin,InID);
        }

        // Store the member information 
        memberInfos.push_back(MemberInfo(InfullName,InphoneNumber,Inemail,InID_type,InID));
}

bool LoginSystem::comparePwd(int userID) {
        short attempt = 0; //number of attempts
        
        //Re-enter password up to 3 times
        while(attempt < 3) {
                //Get password from user
                string pwd;
                cout << "Enter password: ";
                getline(cin, pwd);
                
                //If password is correct, return true
                if(pwd == loginInfos[userID].getPwd()) return true;
                else cout << "Your password is wrong \n";  

                attempt++; //Attempt + 1  
        }
        
        //After 3 times, return false
        cout << "You have entered wrong password 3 times \n";
        return false;
}

//Function to view and update profile information
short LoginSystem::Memberview(int indUser) {
        string choice;
        string newpwd, newFullName, newPhoneNum, newEmail, NewID_type, newID, newCP;
        if (indUser != -1) { //Username is already in the system
                //Display current information
                memberInfos[indUser].terminalDisplay();

                cout << "\nDo you want to update your info?\n";
                cout << "1-Change password\n";
                cout << "2-Change full name\n";
                cout << "3-Change phone number\n"; 
                cout << "4-Change email\n";
                cout << "5-Change ID\n";
                cout << "6-Add Credit Point\n";
                cout << "7-Dashboard\n";
                cout << "Enter your choice: ";
                getline(cin, choice);

                while (choice[0] < '1' || choice[0] > '7' || choice.size() > 1) {
                        cout << "Wrong input! Choose option from 1-6: ";
                        getline(cin, choice);
                }

                //Act based on the choice
                if (choice[0] == '1') {
                        cout << "Enter your new password: ";
                        getline(cin, newpwd);
                        //Check password
                        while (isWeakPwd(newpwd) == false){
                                cout << "Weak password! Please re-enter stronger password: ";
                                getline(cin, newpwd);
                        }
                        loginInfos[indUser].setPwd(newpwd);
                                cout << "Password is changed successfully.\n";
                }

                else if (choice[0] == '2') {
                        cout << "Enter new full name: ";
                        getline(cin, newFullName);
                        while (isValidName(newFullName) == false){
                                cout << "Wrong name input! (Only alpha charater accepted). Re-enter new full name: ";
                                getline(cin, newFullName);
                        }
                        memberInfos[indUser].setFullName(newFullName);
                        cout << "Fullname is changed succesfully.\n";
                }

                else if (choice[0] == '3') {
                        cout << "Enter new phone number: ";
                        getline(cin, newPhoneNum);
                        while (isValidPhoneNumber(newPhoneNum) == false){
                                cout << "Wrong phone number input! (Only number accepted). Re-enter new phone number: ";
                                getline(cin, newPhoneNum);
                        }
                        memberInfos[indUser].setPhoneNum(newPhoneNum);
                        cout << "Phone number is changed successfully.\n";
                }

                else if (choice[0] == '4') {
                        cout << "Enter new email: ";
                        getline(cin, newEmail);
                        while (isValidEmail(newEmail) == false){
                                cout << "Wrong email input! (Email must include '@' and '.'). Re-enter new email: ";
                                getline(cin, newEmail);
                        }
                        memberInfos[indUser].setEmail(newEmail);
                        cout << "Email is changed successfully.\n";
                }

                else if (choice[0] == '5') {
                        //Ask for ID type
                        cout << "Enter your ID type: 1 - Citizen ID or 2 - Passport:  ";
                        getline(cin, NewID_type);
                        //Save ID type
                        memberInfos[indUser].setID_type(NewID_type);
                        
                        //Ask ID
                        cout << "Enter your ID series: "; 
                        getline(cin, newID);
                        //Check if the ID series match the ID type
                        while(!isValidID(NewID_type, newID)) { 
                                cout << "Your ID series does not match the ID type \n";
                                cout << "Enter your ID series again: "; 
                                getline(cin, newID);
                        }
                        //Save ID
                        memberInfos[indUser].setID(newID);
                }
                        
                else if (choice[0] == '6') { //Add CP
                        cout << "Credit Point that you would like to add: ";
                        getline(cin, newCP);

                        while(!is_Int_notNegative(newCP)) {
                                cout << "The input must be integer and is not negative. Enter again: ";
                                getline(cin, newCP);
                        }

                        memberInfos[indUser].setCP(stoi(newCP));
                }
                // else if (choice == 8) cout << "Back to Dashboard!\n";
        }
        return choice[0];       
}

//Function to view username in alphabetical order and view further info
short LoginSystem::usernameList() {
        vector<string> username;
        string U_name;
        // bool check = false;
        short IndUser = -1;

        //Create a vector 'username' to store all the usernames
        for (int i = 0; i < loginInfos.size(); i++){
                username.push_back(loginInfos[i].getUsername());
        }

        //Sort the name in alphabetical order (a->z) and print them out
        sort(username.begin(), username.end());
        cout << "Username list: \n";
        for (int i = 0; i < username.size(); i++){
                cout << username[i] << "\n";
        }
        //Loop to prompt user's input until it match with one of the username in the vector
        while (IndUser == -1) {
                cout << "\nPlease enter a username to view info: ";

                // if (check == false){ //Ignore '\n' only once, otherwise the function wont work properly
                // cin.ignore(1, '\n');
                // check = true;
                // }

                getline(cin, U_name);
                //When username match, break the loop and return IndUser
                for (int i = 0; i < username.size(); i++) {
                if (U_name == username[i]) {
                        IndUser = findUser(U_name);
                        break;
                }
                }
                if (IndUser == -1) {
                cout << "Username not found. Please try again.\n";
                }
        }
        return IndUser;
}        

//Function to display member's personal info for ADMIN and return the name regarding to the index indUser of loginInfos vector
string LoginSystem::adminDisplay(short indUser){
        memberInfos[indUser].terminalDisplay();
        return loginInfos[indUser].getUsername();
}

int LoginSystem::displayCP(int ID) {return memberInfos[ID].getCP();}

double LoginSystem::getRating(int userID) {return memberInfos[userID].getBuyerRating();}

string LoginSystem::getUsername(int userID) {return loginInfos[userID].getUsername();}

void LoginSystem::PayBackCP(string username, int bidValue){
        int userID = findUser(username);
        memberInfos[userID].setCP(bidValue);
}

void LoginSystem::PayForBid(string username, int bidValue){
        int userID = findUser(username);
        memberInfos[userID].setCP(-bidValue);
}

void LoginSystem::SetSellerRating(string sellerName, int rate){
        int userID = findUser(sellerName);
        memberInfos[userID].setSellerRating(rate);
}

void LoginSystem::SetBuyerRating(string buyerName, int rate){
        int userID = findUser(buyerName);
        memberInfos[userID].setBuyerRating(rate);
}

