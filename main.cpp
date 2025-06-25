#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Dashboard.h"
#include "Member.h"
#include "Functions.h"
#include "Items.h"
#include "Admin.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

typedef enum {welcome_screen, Guestview, Memberlogin, Adminlogin, AdminShowInfo, Memberinfo, 
              AccountOverview, ViewActiveItems, Search, searchItemName, SearchCategory, 
              searchRange, Remove, Edit, Rating, Exit} STATES;
STATES state;

int main() {
    //Variables
    state = welcome_screen;
    // short choice = 0;
    // short admchoice = 0;
    // int userID = -1;
    string username, admUsername, admPassword, getname;
    // short memberViewOpt;
    // short AdminUserID = -1;
    short memberViewOpt;
    short check = 0;
    short AdminUserID = -1;
    string searchCategory;
    string category;
    short searchChoice = 0;
    short searchctChoice = 0;
    short ratingChoice = 0;


    //Class
    LoginSystem loginSystem;
    Bidding bidSystem;
    LoginAdmin admin;
    
    //Load Login infos and member infos
    loginSystem.loadMemberData();
    loginSystem.loadLoginData();

    //Load bidding info
    bidSystem.loadBiddingData();
    bidSystem.loadBidderData();
    bidSystem.loadWinnerData();

    //Remove expired items
    bidSystem.winnerRecord(loginSystem);
    bidSystem.expiredItems();
    
    while(1) {
        switch(state) {
            case welcome_screen:
                //Display header 1 time in the program
                static bool displayHeader = false;
                if(displayHeader == false) {
                    header();
                    displayHeader = true;
                }
                
                //Prompt user to choose roles
                char choice;
                choice = appUse();
                if(choice == '1') state = Guestview; //view as guest - DO LATER
                else if(choice == '2') state = Memberlogin; //Login as member
                else if(choice == '3') state = Adminlogin; //Login as admin
                else return -1; //Exit program
            break;
            
            case Guestview:
                Guest_View();
                bidSystem.display_Guest();
                state = welcome_screen;
            break;
            
            case Memberlogin:
                int userID;
                //Get username from user
                username = askUsername();
                
                //Find username in the login system
                userID = loginSystem.findUser(username);
                
                //Username does not exist in the database
                //Ask user to register based on username or view as guest
                if(userID == -1) {
                    //Prompt user to select
                    char opt;
                    opt = Register_Menu();

                    //Guest View
                    if (opt == '1') {
                        state = Guestview;
                    }
                    else if (opt == '2') { //Register new user
                        loginSystem.registerUser(username); //Register password and user info
                        cout << "You have registered successfully!\n\n";
                        state = welcome_screen;
                    }
                    else return -1;
                }

                //Ask user to login
                else {
                    //Get password from user
                    //Compare password in the login system
                    bool pwd = loginSystem.comparePwd(userID);
                    if(pwd == true) {
                        cout << "Login successfully!\n\n";
                        state = AccountOverview;
                    }
                    else if(pwd == false) {
                        cout << "Login Failed!\n";
                        state = Exit;
                    }
                }

            break;

            case AccountOverview:
                cout << "Account Overview: " << username << endl;
                cout << "-------------------------------\n";
                cout << "Active Item Listings: " << bidSystem.number_activeItemsListing(username) << "  |  " << "Active Bids: " << bidSystem.number_activeBids(username) << endl;
                cout << "Items Won: " << bidSystem.itemsWon(username) << "  |  " << "Account Balance: " << loginSystem.displayCP(userID) << " CP" << endl;

                //Active items listing
                ItemListing_Template();
                bidSystem.display_activeItemsListing(username);
                cout << "\n";

                //Active bid
                ActiveBid_Template();
                bidSystem.display_activeBids(username);
                
                //Menu
                char menuOptions;
                menuOptions = accountMenu();

                if (menuOptions == '1') state = Memberinfo;
                else if(menuOptions == '2') bidSystem.createItem(username);
                else if(menuOptions == '3') state = ViewActiveItems;
                else if(menuOptions == '4') state = Search;
                else if(menuOptions == '5') bidSystem.removeBid(username);
                else if(menuOptions == '6') bidSystem.editBid(username);
                else if(menuOptions == '7') state = Rating;
                else state = Exit;
                break;
            case Memberinfo:
                char memberViewOpt;
                memberViewOpt = loginSystem.Memberview(userID);
                if (memberViewOpt == '7'){
                    state = AccountOverview;
                }
            break;

            case ViewActiveItems:
                //List items
                bidSystem.displayItems(loginSystem, loginSystem.getRating(userID), username);
                
                //Menu
                char viewItems_menu;
                viewItems_menu = viewItem_Menu();

                //Go to bid
                if(viewItems_menu == '1') bidSystem.memberBid(loginSystem,userID); //state = BidState;

                //Exit
                else state = AccountOverview;
            break;

            case Adminlogin:
                //Get admin username
                cout << "Enter username of admin account: ";
                getline(cin, admUsername);
                if(!admin.checkUsername(admUsername)) return -1;

                //Get admin password
                cout << "Enter password of admin account: ";
                getline(cin, admPassword);
                if(!admin.checkPassword(admPassword)) return -1;

                cout << "Login successfully!\n";
                state = AdminShowInfo;
            break;

            case AdminShowInfo:
                char admChoice;
                admChoice = adminMenu();
                
                if(admChoice == '1') {
                    short AdminUserID;
                    AdminUserID = -1;
                    AdminUserID = loginSystem.usernameList();
                    //When username match and IndUser value return, display memberinfo
                    if (AdminUserID != -1) {
                        //getname value returned is the one of LoginInfos[UserId].getName()
                        getname = loginSystem.adminDisplay(AdminUserID);
                        cout << "\n";
                        cout << "Account Overview: " << getname << endl;
                        cout << "-------------------------------\n";
                        cout << "Active Item Listings: " << bidSystem.number_activeItemsListing(getname) << "  |  " << "Active Bids: " << 2 << endl;
                        cout << "Items Won: " << bidSystem.itemsWon(getname) << "  |  " << "Account Balance: " << loginSystem.displayCP(AdminUserID) << " CP" << endl;

                        //Active items listing
                        ItemListing_Template();
                        bidSystem.display_activeItemsListing(getname);

                        //Active bid
                        ActiveBid_Template();
                        bidSystem.display_activeBids(getname);
                    }
                }
                else if(admChoice == '2') {
                    ItemListing_Template();
                    bidSystem.display_Admin();
                }
                else state = Exit;

            break;

            case Search:
                searchChoice = search_Menu();
                if (searchChoice == 1) state = searchItemName;
                
                else if (searchChoice == 2) state =SearchCategory;    
            
                else if (searchChoice == 3) state = searchRange;
    
                else state = AccountOverview;
            break; 

            case searchItemName:
                // Search for items by item's name 
                cout << "\nSearch item by name\n";
                searchctChoice = search_Charac_Menu();

                if (searchctChoice == 1) bidSystem.searchItem(loginSystem,userID);
                else if (searchctChoice == 2) state = Search;
            break;

            case SearchCategory:
                // Search for items by category
                cout << "\nSearch item by category\n";
                searchctChoice = search_Charac_Menu();

                if (searchctChoice == 1) bidSystem.searchCategory(loginSystem,userID);
                else if (searchctChoice == 2) state =Search;
            break;

            case searchRange:
                // Search for items by seller rating score
                cout << "\nSearch item by Credit Point range\n";
                searchctChoice = search_Charac_Menu();

                if (searchctChoice == 1) bidSystem.searchCP(loginSystem,userID);
                else if (searchctChoice == 2) state =Search;
            break;

            case Rating:
                ratingChoice = rating_Menu();
                if (ratingChoice == 1) bidSystem.ratingSeller(loginSystem,username);
                
                else if (ratingChoice == 2) bidSystem.ratingBuyer(loginSystem,username);    
            
                else state = AccountOverview;
            break;

            case Exit:
                loginSystem.saveLoginData();
                loginSystem.saveMemberData();
                bidSystem.saveBiddingData();
                bidSystem.saveBidderData();
                bidSystem.saveWinnerData();
                return -1;
            break;

            default:
            break;
        }
    }
    return 0;
}

