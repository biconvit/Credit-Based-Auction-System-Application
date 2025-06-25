#ifndef _ITEMS_H     
#define _ITEMS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Data.h"
#include "Member.h"

using std::cin;
using std::cout;
using std::string;
using std::fstream;
using std::cerr;

#define BIDDINGFILE "BiddingData.dat"
#define BIDDERFILE "BidderData.dat"
#define WINNERFILE "WinnerData.dat"

class Bidders {
    private:
        string user;
        string bidValue;
        string itemName;
        string sellerUsername;
        string endtime;
       
    public:
        Bidders(string user, string bidValue, string itemName, string sellerUsername, string endtime);

    //Getter
    string getUser();
    string getBidValue();
    string getItemName();
    string getSellerUsername();
    string getEndTime();

    //Set
    // void setUser(string user);
    // void setBidValue(string bidValue);

    //Display
    string display();
};

class Items {
    private:
        string sellerUsername;
        string highestBidder; //Store username
        string highestBid;
        string itemName;
        string category; //electronics, weapon, figures
        string description;
        string startBid;
        string increment;
        string startTime;
        string endTime;
        string minBuyer_score;

       
    public:
        //Constructor
        Items(string sellerUsername, string highestBidder, string highestBid, string itemName,  
            string category, string description, string startBid, string increment, string startTime, string endTime, string minBuyer_score);

        //Getter
        string getSellerUsername();
        string getHighestBidder();
        string getHighestBid();        
        string getItemName();
        string getCategory();
        string getDescript();
        string getStartBid();
        string getIncrement();
        string getEndTime();
        string getMinScore();

        //Set
        void setHighestBidder(string highestBidder);
        void setHighestBid(string highestBid);
        void setItemName(string itemName);
        void setCategory(string category);
        void setDescription(string description);
        void setStartBid(string startBid);
        void setIncrement(string increment);
        void setEndTime(string endTime);
        void setMinBuyer(string minBuyer);

        //Display
        string display();
};

class Winner {
    private:
        string winnerName;
        string sellerName;
        string itemName;
        string bidValue;
        string endTime;
        bool seller_rate_buyer;
        bool buyer_rate_seller;

    public:
        //Constructor
        Winner(string winnerName, string sellerName, string itemName, string bidValue, string endTime, bool seller_rate_buyer, bool buyer_rate_seller);

        //display
        string display();

    friend class Bidding;
};


class Bidding {
    private:
        vector<Items> list;
        vector<Bidders> bidderList;
        vector<Winner> winnerList;
    public:
        //Constructor
        Bidding(vector<Items> list = {}, vector<Bidders> bidderList = {}, vector<Winner> winnerList = {});

        //Load and save data from .dat files
        void loadBiddingData();
        void saveBiddingData();
        void loadBidderData();
        void saveBidderData();
        void loadWinnerData();
        void saveWinnerData();

        //Other methods
        void createItem(string username);
        void display_Guest();
        void display_Admin();
        int number_activeItemsListing(string username);
        int number_activeBids(string username);
        void display_activeItemsListing(string username);
        void display_activeBids(string username);
        void displayItems(LoginSystem &LoginSystem, const double &rating, const string username);
        bool findItems(double rating, string itemName, string sellerName);
        void memberBid(LoginSystem &LoginSystem, int userID);
        void removeBid(string username);
        void editBid(string username);
        void winnerRecord(LoginSystem &LoginSystem);
        int itemsWon(string username);
        void expiredItems();      
        void searchCategory(LoginSystem &LoginSystem, int userID);
        void searchItem(LoginSystem &LoginSystem, int userID);
        void searchCP(LoginSystem &LoginSystem, int userID);
        void ratingSeller(LoginSystem &LoginSystem, string username);
        void ratingBuyer(LoginSystem &LoginSystem, string username);

        friend class LoginSystem;
};
#endif