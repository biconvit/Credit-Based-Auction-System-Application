#include <iostream>
#include <vector>
#include <string>
#include "Items.h"
#include "Functions.h"

using std::string;
using std::cout;
using std::cin;

//Bidders class

//Constructor
Bidders::Bidders(string user = "", string bidValue = "", string itemName = "", string sellerUsername = "", string endtime = "") 
                : user(user), bidValue(bidValue), itemName(itemName), sellerUsername(sellerUsername), endtime(endtime) {}

//Getter
string Bidders::getUser() {return user;}
string Bidders::getBidValue() {return bidValue;}
string Bidders::getItemName() {return itemName;}
string Bidders::getSellerUsername() {return sellerUsername;}
string Bidders::getEndTime() {return endtime;}


//Set
// void Bidders::setUser(string user) {this->user = user;}
// void Bidders::setBidValue(string bidValue) {this->bidValue = bidValue;}

//Display
string Bidders::display() {return user + "_" + bidValue + "_" + itemName + "_" + sellerUsername + "_" + endtime + "\n";}


//Items class

//Constructor
Items::Items(string sellerUsername = "", string highestBidder = "", string highestBid = "", string itemName = "",  
             string category = "", string description = "", string startBid = "", string increment = "", 
             string startTime = "", string endTime = "", string minBuyer_score = "")
             :sellerUsername(sellerUsername), highestBidder(highestBidder), highestBid(highestBid), itemName(itemName),
              category(category), description(description), startBid(startBid), increment(increment),
              startTime(startTime), endTime(endTime), minBuyer_score(minBuyer_score) {}

//Getter
string Items::getSellerUsername() {return sellerUsername;}
string Items::getHighestBidder() {return highestBidder;}
string Items::getHighestBid() {return highestBid;}       
string Items::getItemName() {return itemName;}
string Items::getCategory() {return category;}
string Items::getDescript() {return description;}
string Items::getStartBid() {return startBid;}
string Items::getIncrement() {return increment;}
string Items::getEndTime() {return endTime;}
string Items::getMinScore() {return minBuyer_score;}

//Set
void Items::setHighestBidder(string highestBidder) {this->highestBidder = highestBidder;}
void Items::setHighestBid(string highestBid) {this->highestBid = highestBid;}
void Items::setItemName(string itemName) {this->itemName = itemName;}
void Items::setCategory(string category) {this->category = category;}
void Items::setDescription(string description) {this->description = description;}
void Items::setStartBid(string startBid) {this->startBid = startBid;}
void Items::setIncrement(string increment)  {this->increment = increment;}
void Items::setEndTime(string endTime)  {this->endTime = endTime;}
void Items::setMinBuyer(string minBuyer)  {this->minBuyer_score = minBuyer;}

//display
string Items::display(){return sellerUsername + "_" + highestBidder + "_" + highestBid + "_" + itemName + "_" + category + "_" +
                                description + "_"  + startBid + "_" + increment + "_" + startTime + "_" + endTime + "_" + minBuyer_score + "\n";}

//Winner class

//Constructor
Winner::Winner(string winnerName = "", string sellerName = "", string itemName = "", string bidValue = "", string endTime = "", bool seller_rate_buyer = false, bool buyer_rate_seller = false)
            : winnerName(winnerName), sellerName(sellerName), itemName(itemName), bidValue(bidValue), endTime(endTime), seller_rate_buyer(seller_rate_buyer), buyer_rate_seller(buyer_rate_seller) {}

string Winner::display() {return winnerName + "_" + sellerName + "_" + itemName + "_" + bidValue + "_" + endTime + "_" + std::to_string(seller_rate_buyer) + "_" + std::to_string(buyer_rate_seller) +"\n";}

//Bidding class

//Constructor
Bidding::Bidding(vector<Items> list, vector<Bidders> bidderList, vector<Winner> winnerList) : list(list), bidderList(bidderList), winnerList(winnerList) {}

//Load bidding data
void Bidding::loadBiddingData() {
    //Check whether file exist. If not, create a new one
        tryOpenFile(BIDDINGFILE);

        //Load Login Info
        fstream biddingData;

        //Try to open file to read
        biddingData.open(BIDDINGFILE, std::ios::in);
        //Check whether file is opened
        if(!biddingData) {
                cerr << "Failed to open file!\n";
                return;
        }

        //Temporary variables
        string username;
        string highestName;
        string highestPrice;
        string item;
        string ctgy;
        string descript;
        string startPrice;
        string incre;
        string start;
        string end;
        string minRating_score;

        //Get data from Login file
        while(biddingData.peek() != EOF) {
                getline(biddingData, username, '_');
                getline(biddingData, highestName, '_');
                getline(biddingData, highestPrice, '_');
                getline(biddingData, item, '_');
                getline(biddingData, ctgy, '_');
                getline(biddingData, descript, '_');
                getline(biddingData, startPrice, '_');
                getline(biddingData, incre, '_');
                getline(biddingData, start, '_');
                getline(biddingData, end, '_');
                getline(biddingData, minRating_score, '\n');

                //push back login data
                list.push_back(Items(username, highestName, highestPrice, item, ctgy, descript, startPrice, incre, start, end, minRating_score));
        }

        biddingData.close();
}

//Save bidding data
void Bidding::saveBiddingData() {
    fstream biddingData;
        
    //Try to open file to write
    biddingData.open(BIDDINGFILE, std::ios::out);
    //Check whether file is opened
    if(!biddingData) {
            cerr << "Failed to open file!\n";
            return;
    }

    for(Items &i : list) biddingData << i.display();

    biddingData.close();

    cout << "Bidding Data is saved!\n";
}

void Bidding::loadBidderData() {
    //Check whether file exist. If not, create a new one
    tryOpenFile(BIDDERFILE);

    //Load Login Info
    fstream bidderData;

    //Try to open file to read
    bidderData.open(BIDDERFILE, std::ios::in);
    //Check whether file is opened
    if(!bidderData) {
            cerr << "Failed to open file!\n";
            return;
    }

    //Temporary variables
    string bidderName;
    string bidValue;
    string itemName;
    string sellerUsername;
    string endtime;

    //Get data from bidder file
    while(bidderData.peek() != EOF) {
        getline(bidderData,bidderName,'_');
        getline(bidderData,bidValue,'_');
        getline(bidderData,itemName,'_');
        getline(bidderData,sellerUsername,'_');
        getline(bidderData,endtime,'\n');

        //save to bidderList
        bidderList.push_back(Bidders(bidderName, bidValue, itemName, sellerUsername, endtime));
    }

    bidderData.close();
}

void Bidding::saveBidderData() {
    fstream bidderData;
        
    //Try to open file to write
    bidderData.open(BIDDERFILE, std::ios::out);
    //Check whether file is opened
    if(!bidderData) {
            cerr << "Failed to open file!\n";
            return;
    }

     //Save bidderList to BIDDERFILE
    for(Bidders &i : bidderList) bidderData << i.display();
       
    bidderData.close();

    cout << "Bidders Data is saved!\n";
}

void Bidding::loadWinnerData() {
    //Check whether file exist. If not, create a new one
    tryOpenFile(WINNERFILE);

    //Load Login Info
    fstream winnerData;

    //Try to open file to read
    winnerData.open(WINNERFILE, std::ios::in);
    //Check whether file is opened
    if(!winnerData) {
            cerr << "Failed to open file!\n";
            return;
    }

    //Temporary variables
    string winnerName, sellerName, itemName, bidValue, endTime, seller_rate_buyer, buyer_rate_seller;

    //Get data from winner file
    while(winnerData.peek() != EOF) {
        getline(winnerData,winnerName,'_');
        getline(winnerData,sellerName,'_');
        getline(winnerData,itemName,'_');
        getline(winnerData,bidValue,'_');
        getline(winnerData,endTime,'_');
        getline(winnerData,seller_rate_buyer,'_');
        getline(winnerData,buyer_rate_seller,'\n');
          

        //save to bidderList
        winnerList.push_back(Winner(winnerName, sellerName, itemName, bidValue, endTime, stoi(seller_rate_buyer), stoi(buyer_rate_seller)));
    }

    winnerData.close();
}

void Bidding::saveWinnerData() {
    fstream winnerData;
        
    //Try to open file to write
    winnerData.open(WINNERFILE, std::ios::out);
    //Check whether file is opened
    if(!winnerData) {
            cerr << "Failed to open file!\n";
            return;
    }

    for(Winner &i : winnerList) winnerData << i.display();

    winnerData.close();

    cout << "Winner Data is saved!\n";
}

void Bidding::createItem(string username) {
    cout << "\nPlease provide item's information to create\n";
    string itemName, category, description, startBid, bidIncreasement, endTime, minBuyer_score;
    
    //Get item's name and check validity
    cout << "Item's name: "; getline(cin,itemName);
    while(!isValid_ItemName(itemName)) {
        cout << "Enter item's name again: "; getline(cin,itemName);
    }

    //Get category and check validity
    cout << "Category: "; getline(cin,category);
    while(!isValid_Category(category)) {
        cout << "There are 3 categories including Weapon, Figure and Electronics!\n";
        cout << "Enter category again: "; getline(cin,category);
    }
    
    //Get short description and check validity
    cout << "Short description: "; getline(cin,description);
    while(!isValid_Description(description)) {
        cout << "Enter description again: "; getline(cin,description);
    }

    //Get start bid and check validity
    cout << "Start Bid: "; getline(cin,startBid);
    while(!is_Int_notNegative(startBid)) {
        cout << "Start bid must be an integer and cannot be negative!\n";
        cout << "Enter start bid again: "; getline(cin,startBid);
    }
    
    //Get increment and check validity
    cout << "Increment: "; getline(cin,bidIncreasement);
    while(!is_Int_notNegative(bidIncreasement)) {
        cout << "Increment must be an integer and cannot be negative!\n";
        cout << "Enter increment again: "; getline(cin,bidIncreasement);
    }

    //Get end time and check validity
    cout << "End Time includes month/day/year/hour - MM/DD/YYYY/HH: "; getline(cin,endTime);
    while(!isValidEndTime(endTime)){
        cout << "Invalid end time\n";
        cout << "Enter again end Time includes month/day/year/hour - MM/DD/YYYY/HH: "; getline(cin,endTime);
    }

    //Get minimum buyer score and check
    cout << "Minimum buyer rating score from 1 to 5: "; getline(cin,minBuyer_score);
    while(!isValid_MinBuyer(minBuyer_score)){
        cout << "Invalid minimum buyer\n";
        cout << "Enter minimum buye again: "; getline(cin,minBuyer_score);
    }

    //Push back new item to list
    list.push_back(Items(username,"NA","0",itemName,category,description,startBid,bidIncreasement,std::to_string(getCurrentTime()),endTime,minBuyer_score));

}

void Bidding::display_Guest() {
    int count = 1;
    for(auto &i : list) {
        cout << std::left << std::setw(5) << count
            << std::setw(32) << i.getItemName()
            << std::setw(15) << i.getCategory()
            << std::setw(150) << i.getDescript() << endl;

        count++;
    }
    cout << "\n";
}

void Bidding::display_Admin() {
    int count = 1;
    for(auto &i : list) {
        cout << std::left << std::setw(5) << count 
            << std::setw(32) << i.getItemName() 
            << std::setw(15) << i.getCategory();

        if(i.getHighestBid() == "0") cout << std::setw(15) << i.getStartBid();
        else cout << std::setw(15) << i.getHighestBid();

        cout << std::setw(25) << i.getHighestBidder()
            << std::setw(25)<< getFormattedEndTime(i.getEndTime()) << endl;

        count++;
    }
}

int Bidding::number_activeItemsListing(string username) {
    int count = 0;
    for(auto &i : list) {
        if(i.getSellerUsername() == username) count++;
    }

    return count;
}

int Bidding::number_activeBids(string username) {
    vector<string> items_name = {};
    vector<string> seller_name = {};
    vector<string> endtime = {};

    //Get current bid item's name of username
    for(int i = 0; i < bidderList.size(); i++){
        if((username == bidderList[i].getUser())){
            if(items_name.empty()){
                items_name.push_back(bidderList[i].getItemName());
                seller_name.push_back(bidderList[i].getSellerUsername());
                endtime.push_back(bidderList[i].getEndTime()); 
            }

            int hasItem = 0;
            for(int j = 0; j < items_name.size(); j++){
                if(bidderList[i].getItemName() == items_name[j] && bidderList[i].getSellerUsername() == seller_name[j]){
                    hasItem++;
                }
            }

            if(hasItem < 1){
                items_name.push_back(bidderList[i].getItemName());
                seller_name.push_back(bidderList[i].getSellerUsername());
                endtime.push_back(bidderList[i].getEndTime());
            }
        }    
    }

    return (int) items_name.size();
}

void Bidding::display_activeItemsListing(string username) {
    int count = 1;
    bool hasItem = false;
    for(int i = 0; i < (int) list.size(); i++) {
        if((username == list[i].getSellerUsername())) {
            cout << std::left << std::setw(5) << count 
            << std::setw(32) << list[i].getItemName() 
            << std::setw(15) << list[i].getCategory();

            if(list[i].getHighestBid() == "0") cout << std::setw(15) << list[i].getStartBid();
            else cout << std::setw(15) << list[i].getHighestBid();

            cout << std::setw(25) << list[i].getHighestBidder()
            << std::setw(25)<< getFormattedEndTime(list[i].getEndTime()) << endl;
            count++;
            hasItem = true;
        }
    }

    if(!hasItem) cout << "You have no item listing yet!\n";
}

void Bidding::display_activeBids(string username) {
    // find current bid items of the username
    vector<string> items_name = {};
    vector<string> seller_name = {};
    vector<string> category = {};
    vector<int> your_bid = {};
    vector<string> current_bid = {};
    vector<string> endDate_time = {};

    if(bidderList.empty()){
        cout << "You dont have any bid yet\n" << endl;
        return;
    }

    //Get current bid item's name of username
    for(int i = 0; i < bidderList.size(); i++){
        if((username == bidderList[i].getUser())){
            // if(winnerList.empty()){
                 if(items_name.empty()){
                        items_name.push_back(bidderList[i].getItemName());
                        seller_name.push_back(bidderList[i].getSellerUsername());
                    }

                    int hasItem = 0;
                    for(int j = 0; j < items_name.size(); j++){
                        if(bidderList[i].getItemName() == items_name[j] && bidderList[i].getSellerUsername() == seller_name[j]){
                            hasItem++;
                        }
                    }

                    if(hasItem < 1){
                        items_name.push_back(bidderList[i].getItemName());
                        seller_name.push_back(bidderList[i].getSellerUsername());
                    }
            // }
            // else {
            //     bool sold = false;
            //     for(auto &winner : winnerList){
            //         //if(winner.winnerName != username || winner.itemName != bidderList[i].getItemName() || winner.sellerName != bidderList[i].getSellerUsername()){
            //         if(winner.itemName == bidderList[i].getItemName() && winner.sellerName == bidderList[i].getSellerUsername()){
            //            sold = true;
            //         }
            //     }

            //     if(!sold){
            //         if(items_name.empty()){
            //             items_name.push_back(bidderList[i].getItemName());
            //             seller_name.push_back(bidderList[i].getSellerUsername());
            //         }

            //         int hasItem = 0;
            //         for(int j = 0; j < items_name.size(); j++){
            //             if(bidderList[i].getItemName() == items_name[j] && bidderList[i].getSellerUsername() == seller_name[j]){
            //                 hasItem++;
            //             }
            //         }

            //         if(hasItem < 1){
            //             items_name.push_back(bidderList[i].getItemName());
            //             seller_name.push_back(bidderList[i].getSellerUsername());
            //         }
            //     }
            // }
                   
        }    
    }

    if(items_name.empty()){
        cout << "You dont have any bid yet\n" << endl;
        return;
    }

    //Get current bid item's category bid of username  & highest current bid & end date
    for(int i = 0; i < items_name.size(); i++){
        for(auto &k : list){
            if(k.getItemName() == items_name[i] && k.getSellerUsername() == seller_name[i]){
                category.push_back(k.getCategory());
                current_bid.push_back(k.getHighestBid());
                endDate_time.push_back(k.getEndTime());         
            }
        }
    }

    //Get the lastest bid
    for(int i = 0; i < items_name.size(); i++){
        int max_ur_bid = 0;
        for(auto &k : bidderList){
            if(items_name[i] == k.getItemName() && seller_name[i] == k.getSellerUsername() && username == k.getUser()){
                if(stoi(k.getBidValue()) > max_ur_bid){
                    max_ur_bid = stoi(k.getBidValue());
                }
            }
        }
        your_bid.push_back(max_ur_bid);
    }

    for(int i = 0; i < items_name.size(); i++){
        if(category[i] == ""){
            items_name.erase(items_name.begin()+i);
            seller_name.erase(seller_name.begin()+i);
            category.erase(category.begin()+i);
            your_bid.erase(your_bid.begin()+i);
            current_bid.erase(current_bid.begin()+i);
            endDate_time.erase(endDate_time.begin()+i);
            cout << "delete succesfully\n";
        }
    }

    //print out to terminal
    int count = 1;
    for(int i = 0; i < (int) items_name.size(); i++) {
            cout << std::left << std::setw(5) << count 
            << std::setw(32) << items_name[i]
            << std::setw(15) << category[i]
            << std::setw(15) << your_bid[i]
            << std::setw(25) << current_bid[i]
            << std::setw(25) << seller_name[i]
            << std::setw(25)<< getFormattedEndTime(endDate_time[i]) << endl;
            count++;
            
    }
    
}

void Bidding::displayItems(LoginSystem &LoginSystem, const double &rating, const string username){
    cout << std::left 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(15) << "Seller" 
        << std::setw(15) << "Current bid" 
        << std::setw(25) << "Increment"
        << std::setw(25) << "End Date & Time" 
        << std::setw(25) << "Seller rating" << endl;


    for(Items &i : list) {
        // Check rating
        if(rating >= std::stod(i.getMinScore()) && username != i.getSellerUsername()) {
            //does not have highest bid yet, display startbid as the highest
            if(i.getHighestBid() != "" && i.getHighestBid() != "NA"){
                cout << std::left 
                << std::setw(32) << i.getItemName() 
                << std::setw(15) << i.getCategory() 
                << std::setw(15) << i.getSellerUsername();
                
                if(i.getHighestBid() == "0") cout << i.getStartBid() << std::setw(13) << " (Start)";
                else cout << std::setw(15) << i.getHighestBid();

                cout << std::setw(25) << i.getIncrement() 
                << std::setw(25)<< getFormattedEndTime(i.getEndTime());

                for(int k = 0; k < LoginSystem.loginInfos.size(); k ++){
                    if(LoginSystem.loginInfos[k].getUsername() == i.getSellerUsername()){
                        cout << std::setw(25) << std::fixed << std::setprecision(2) << LoginSystem.memberInfos[k].getSellerRating() << endl;
                    }
                }
            }
            else {
                cout << std::left 
                << std::setw(32) << i.getItemName() 
                << std::setw(15) << i.getCategory()
                << std::setw(15) << i.getSellerUsername() 
                << std::setw(15) << i.getStartBid()
                << std::setw(25) << i.getIncrement()
                << std::setw(25)<< getFormattedEndTime(i.getEndTime());

                for(int k = 0; k < LoginSystem.loginInfos.size(); k ++){
                    if(LoginSystem.loginInfos[k].getUsername() == i.getSellerUsername()){
                        cout << std::setw(25) << std::fixed << std::setprecision(2) << LoginSystem.memberInfos[k].getSellerRating() << endl;
                    }
                }
            }
        } 
    }
}

bool Bidding::findItems(double rating, string itemName, string sellerName){
    for(Items &i : list){
        if(itemName == i.getItemName() && sellerName == i.getSellerUsername() && rating >= std::stod(i.getMinScore()))  return true;
    }
    return false;
}

void Bidding::memberBid(LoginSystem &LoginSystem, int userID) {
    string itemName, sellerName;
    cout << "\nEnter item name: " ; getline(cin,itemName);
    cout << "Enter seller name of " << itemName << ": "; getline(cin,sellerName);

    double rating = LoginSystem.getRating(userID);

    // Check the existance of item and sellerName
    while(!findItems(rating, itemName, sellerName)){
        cout << "Item name & seller name are not in the list\n";
        cout << "Enter item name again: " ; getline(cin,itemName);
        cout << "Enter seller name of " << itemName << " again: "; getline(cin,sellerName);
    }

    //Check the end time to avoid bid after the endtime
    for(Items &i : list){
         if(itemName == i.getItemName() && sellerName == i.getSellerUsername() && rating >= std::stod(i.getMinScore())){
            //Extract each date & time element
            std::stringstream ss(i.getEndTime());
            string month, day, year, hour;
            getline(ss, month, '/');
            getline(ss, day, '/');
            getline(ss, year, '/');
            getline(ss, hour, '/');

            //Conver to int
            int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

            if(getCurrentTime() > getEndTime_sec(iMonth, iDay, iYear, iHour)){
                cout << "The aution of " << itemName << " was end, you can not make any bid\n";
                return;
            }
        }
    }

    //Find highest bid of item
    string highestBid, increment, startBid;
    for(Items &i : list){
        if(itemName == i.getItemName() && sellerName == i.getSellerUsername() && rating >= std::stod(i.getMinScore())) {
            highestBid = i.getHighestBid();
            increment = i.getIncrement();
            startBid = i.getStartBid();
        }
    }

    //Enter bid value
    string bidValue;
    cout << "Enter your bid: "; getline(cin,bidValue);
    

    int CP = LoginSystem.displayCP(userID);

    if(!isBidValueValid(std::stoi(bidValue), CP, std::stoi(highestBid), std::stoi(increment), std::stoi(startBid))) return; // enough cp, sastisfy increment, 
    
    string username = LoginSystem.getUsername(userID); // find username
    //Update bidderList (include all the bid action from all users)
    int maxBid_index = 0;
    int maxBid = 0;
    string maxBid_username;
    for(Items &j : list){
        if(j.getItemName() == itemName && j.getSellerUsername() == sellerName && j.getHighestBidder() == "NA"){ // new bid from blank
            //Add new bid
            LoginSystem.PayForBid(username,std::stoi(bidValue));
            bidderList.push_back(Bidders(username,bidValue,itemName,sellerName, j.getEndTime()));
        }
        else if(j.getItemName() == itemName && j.getSellerUsername() == sellerName && j.getHighestBidder() != "NA"){
            // find previous maximum of Item
            for(int i = 0; i < bidderList.size(); i++){
                if(bidderList[i].getItemName() == itemName && bidderList[i].getSellerUsername() == sellerName){
                    if(stoi(bidderList[i].getBidValue()) > maxBid){
                        maxBid = stoi(bidderList[i].getBidValue());
                        maxBid_index = i;
                        maxBid_username = bidderList[i].getUser();
                    }
                }
            }

            //Return CP for highest previous bidder
            LoginSystem.PayBackCP(maxBid_username,maxBid);

            //Take CP from the current bidder and Save bid to bidderList
            LoginSystem.PayForBid(username,std::stoi(bidValue));
            bidderList.push_back(Bidders(username,bidValue,itemName,sellerName, j.getEndTime()));
        } 
    }

    //Update current bid - Update highest bid, highest bidder, -CP, -CP bonus,
    for(Items &i : list){
        if(i.getItemName() == itemName && i.getSellerUsername() == sellerName){
            i.setHighestBidder(username);
            i.setHighestBid(bidValue);
        }
    }
}

void Bidding::searchItem(LoginSystem &LoginSystem, int userID) {
    string itemName;
    cout << "Enter item name: " ; getline(cin,itemName);
    
    bool hasItem = false;

    cout << "From  your search:\n";
    cout << "-------------------------------\n";
    cout << std::left 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(15) << "Seller" 
        << std::setw(15) << "Current bid" 
        << std::setw(25) << "Current bidder" 
        << std::setw(25) << "End Date & Time" << endl;
    for(Items &i : list) {
        if(itemName == i.getItemName() && LoginSystem.getRating(userID) >= stod(i.getMinScore())) {
            cout << std::left 
            << std::setw(32) << i.getItemName() 
            << std::setw(15) << i.getCategory() 
            << std::setw(15) << i.getSellerUsername();
            
            if(i.getHighestBid() == "0") cout << std::setw(15) << i.getStartBid();
            else cout << std::setw(15) << i.getHighestBid();

            cout << std::setw(25) << i.getHighestBidder() 
            << std::setw(25)<< getFormattedEndTime(i.getEndTime()) << endl;
            
            // break;
            hasItem = true;
        }
    }
    
    //No items match
    if(!hasItem) cout << "-------------------------------\n" << "No matching item!\n";
    else cout << "\n";
}

void Bidding::removeBid(string username){
    //check if user created bid
    bool hasUser = false;
    for(Items &i : list){
        if(i.getSellerUsername() == username) hasUser = true;
    }
    if(!hasUser) {
        cout << "\nYou have not created any item for bid\n";
        return;
    }

    // Ask for item to remove
    bool hasItem = false;
    string itemName;
    cout << "\nEnter item want to remove: ";
    getline(cin,itemName);

    for(auto &i : list){
        if(i.getSellerUsername() == username && i.getItemName() == itemName) hasItem = true;
    }

    //check for existance of item with seller
    if(!hasItem){
        cout << "You dont have " << itemName << " on your list\n";
        return;
    }
    else {
        for(int i = 0; i <list.size(); i++){
            if(list[i].getSellerUsername() == username && list[i].getItemName() == itemName){ // find based on username and item name
                if(list[i].getHighestBidder() == "NA" && list[i].getHighestBid() == "0"){ // check if it has been bid
                    list.erase(list.begin()+i);
                    cout <<  list[i].getItemName() << " remove succesfully\n";
                    return; // exit
                }
                else if(list[i].getHighestBidder() != "NA" || list[i].getHighestBid() != "0") {
                    cout << "Your item: \"" << itemName << "\" has already been bid, you can not remove\n";
                    return; // exit
                }
               
            }
        }
    }
}

void Bidding::editBid(string username){
    //check if user already created bid
    bool hasUser = false;
    for(Items &i : list){
        if(i.getSellerUsername() == username) hasUser = true;
    }
    if(!hasUser) {
        cout << "\nYou have not created any item for bid\n";
        return;
    }

    // Ask for item to edit
    string itemName;
    cout << "\nEnter item want to edit: "; 
    getline(cin,itemName);

    //check for existance of item with seller, not have any bid yet and get the position
    bool hasItem = false;
    bool notBid = false;
    int index = 0;
    for(int i = 0; i <list.size(); i++){
        if(list[i].getSellerUsername() == username && list[i].getItemName() == itemName){
            hasItem = true;
            if(list[i].getHighestBidder() == "NA" && list[i].getHighestBid() == "0"){
                notBid = true;
                index = i;
            } 
            break;
        }
    }
    
    // Check if has Item
    if(!hasItem){
        cout << "You dont have " << itemName << " on your list\n";
        return;
    }
    //  Check if Item not have any bid yet
    if(!notBid) {
        cout << itemName <<" has already bidded, you cannot modify\n";
        return;
    }

    vector<string> characArr= {"Item name", "Category", "Short description", "Start bid", "Increment", "End time", "Minimum buyer score"};
    
    // Print out editable chracteristic 
    cout << "There are some characteristics of item you are able to edit: \n";
    for(int i = 0; i < characArr.size(); i++){
        if(i == characArr.size() - 1){
            cout << i + 1 << "." <<characArr[i] << endl;
        }
        else cout << i + 1 <<"."<< characArr[i] << " - ";
    }

    // Asker for characteristic to edit
    string choice;
    cout << "\nEnter the number characteristic want to edit as (1, 2, ...): "; 
    getline(cin,choice);

    //check for valid input characteristic
    bool validCharac = false;
    if(choice[0] >= '1' && choice[0] <= '7' && choice.length() == 1){
        validCharac = true;
    }

    // Change the characteristic
    string editContent;
    if(!validCharac){
        cout << "Your input does not match any characteristic on the list\n";
        return;
    }
    else {
        cout << "Enter new " <<characArr[choice[0] - 48 - 1]<<": ";
        getline(cin, editContent);

        //check validation
        if(choice[0] == '1') { // Item name 
            while(!isValid_ItemName(editContent)) { // check for valid Item name
            cout << "Only alphanumerics and blanks are allowed!\n";
            cout << "Enter item's name again: "; getline(cin,editContent);
            }
            list[index].setItemName(editContent); // Update new Item name
        }
        else if(choice[0] == '2') { //Category
            while(!isValid_Category(editContent)) {
                cout << "There are 3 categories including Weapon, Figure and Electronics!\n";
                cout << "Enter category again: "; getline(cin,editContent);
            }
            list[index].setCategory(editContent); // Update new category
        }
        else if(choice[0] == '3') { //Description
            while(!isValid_Description(editContent)) {
                cout << "Only alphanumerics and blanks are allowed!\n";
                cout << "Enter description again: "; getline(cin,editContent);
            }
            list[index].setDescription(editContent); // Update new description
        }
        else if(choice[0] == '4'){ // Start bid
            while(!is_Int_notNegative(editContent)) {
                cout << "Start bid must be an integer and cannot be negative!\n";
                cout << "Enter start bid again: "; getline(cin,editContent);
            }
            list[index].setStartBid(editContent); // Update new start bid
        }
        else if(choice[0] == '5'){ // Increment
            while(!is_Int_notNegative(editContent)) {
                cout << "Increment must be an integer and cannot be negative!\n";
                cout << "Enter increment again: "; getline(cin,editContent);
            }
            list[index].setIncrement(editContent); // Update new start bid
        }
        else if(choice[0] == '6'){
            while(!isValidEndTime(editContent)){
                cout << "Invalid end time\n";
                cout << "Enter again end Time includes month/day/year/hour - MM/DD/YYYY/HH: "; getline(cin,editContent);
            }
            list[index].setEndTime(editContent); // Update new  end Time
        }
        else if(choice[0] == '7'){
            while(!isValid_MinBuyer(editContent)){
                cout << "Invalid minimum buyer\n";
                cout << "Enter minimum buyer score again: "; getline(cin,editContent);
            }
            list[index].setMinBuyer(editContent); // Update new minimum buyer
        }         
    }   
}  
            
 void Bidding::searchCategory(LoginSystem &LoginSystem, int userID) {
    string searchCategory;
    cout << "input search: (Weapon | Electronics | Figure): " ; 
    getline(cin, searchCategory);
     
    while(isValid_SearchCategory(searchCategory) == false) {
        cout << "Wrong category, please input again: "; 
        getline(cin, searchCategory); 
    }  

        bool found = false;

        cout << "From  your search:\n";
        cout << "-------------------------------\n";
        cout << std::left 
            << std::setw(32) << "Name" 
            << std::setw(15) << "Category" 
            << std::setw(15) << "Seller" 
            << std::setw(15) << "Current bid" 
            << std::setw(25) << "Current bidder" 
            << std::setw(25) << "End Date & Time" << endl;
        if (isValid_SearchCategory(searchCategory)) {
            for(Items &i : list){
                if(searchCategory == i.getCategory() && LoginSystem.getRating(userID) >= stod(i.getMinScore())){
                    cout << std::left 
                    << std::setw(32) << i.getItemName() 
                    << std::setw(15) << i.getCategory() 
                    << std::setw(15) << i.getSellerUsername();
                    
                    if(i.getHighestBid() == "0") cout << std::setw(15) << i.getStartBid();
                    else cout << std::setw(15) << i.getHighestBid();
                    
                    cout << std::setw(25) << i.getHighestBidder() 
                    << std::setw(25)<< getFormattedEndTime(i.getEndTime()) << endl;
                    
                    found = true;
                    // break;

                }
                
            }
        }

        if(!found) cout << "-------------------------------\n" << "No matching item!\n";
        else cout << "\n";
}

void Bidding::searchCP(LoginSystem &LoginSystem, int userID) {
    bool hasItem = false;

    string minSeller_credictpoint;
    string maxSeller_credictpoint;
    cout << "Enter minimum CP: " ; 
    getline(cin, minSeller_credictpoint);
    
    while(!isValid_inputCreditPoint(minSeller_credictpoint)) {
        cout << "Wrong input, please input again "; getline(cin, minSeller_credictpoint);
    }

    if(isValid_inputCreditPoint(minSeller_credictpoint)) {
        cout << "Enter maximum CP: " ;  getline(cin, maxSeller_credictpoint);
        while(!isValid_inputCreditPoint(maxSeller_credictpoint)) {
            cout << "Wrong input, please input again "; getline(cin, maxSeller_credictpoint);
        }
    }


    cout << "You have search range credict point from: $"<<  minSeller_credictpoint<< " to $"<<maxSeller_credictpoint <<"\n";
    cout << "From  your search:\n";
    cout << "-------------------------------\n";
    cout << std::left 
        << std::setw(32) << "Name" 
        << std::setw(15) << "Category" 
        << std::setw(15) << "Seller" 
        << std::setw(15) << "Current bid" 
        << std::setw(25) << "Current bidder" 
        << std::setw(25) << "End Date & Time" << endl;
    if(isValid_inputCreditPoint(maxSeller_credictpoint)) {
        for(Items &i : list) {
            if(stoi(i.getHighestBid()) >= stoi(minSeller_credictpoint) && stoi(i.getHighestBid()) <= stoi(maxSeller_credictpoint) && LoginSystem.getRating(userID) >= stod(i.getMinScore())) {
                cout << std::left 
                << std::setw(32) << i.getItemName() 
                << std::setw(15) << i.getCategory() 
                << std::setw(15) << i.getSellerUsername();
                
                if(i.getHighestBid() == "0") cout << std::setw(15) << i.getStartBid();
                else cout << std::setw(15) << i.getHighestBid();
                
                cout << std::setw(25) << i.getHighestBidder() 
                << std::setw(25)<< getFormattedEndTime(i.getEndTime()) << endl;
                

                hasItem = true;
            }
        }
    }

    if(!hasItem) cout << "-------------------------------\n" << "No matching item!\n";
    else cout << "\n";
}

void Bidding::winnerRecord(LoginSystem &LoginSystem){
    string winnerName, sellerName, itemName, bidValue, endTime;
    //Find expired items
    for(int i = 0; i < (int) list.size(); i++) {
        //Extract each date & time element
        std::stringstream ss(list[i].getEndTime());
        string month, day, year, hour;
        getline(ss, month, '/');
        getline(ss, day, '/');
        getline(ss, year, '/');
        getline(ss, hour, '/');

        //Conver to int
        int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

        //If end time is bigger than current time, get the Winner & Item data
        if(list[i].getHighestBidder() != "NA") {
            if(getCurrentTime() > getEndTime_sec(iMonth, iDay, iYear, iHour)){
                winnerName = list[i].getHighestBidder();
                sellerName = list[i].getSellerUsername();
                itemName = list[i].getItemName();
                bidValue = list[i].getHighestBid();
                endTime = list[i].getEndTime();
                winnerList.push_back(Winner(winnerName, sellerName, itemName, bidValue, endTime));
                
                //Add CP to the seller after auction done
                LoginSystem.PayBackCP(sellerName, stoi(bidValue));
            }
        }
    }
}

int Bidding::itemsWon(string username){
    int numOfWon = 0;
    for(auto &i : winnerList){
        if(i.winnerName == username){
            numOfWon++;
        }
    }
    return numOfWon;
}

void Bidding::expiredItems() {
    vector<int> position = {};

    //Find expired items in list
    for(int i = 0; i < (int) list.size(); i++) {
        //Extract each date & time element
        std::stringstream ss(list[i].getEndTime());
        string month, day, year, hour;
        getline(ss, month, '/');
        getline(ss, day, '/');
        getline(ss, year, '/');
        getline(ss, hour, '/');

        //Conver to int
        int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

        //If end time is bigger than current time, save the position index of that item
        if(getCurrentTime() > getEndTime_sec(iMonth, iDay, iYear, iHour)) position.push_back(i);
    }

    //Delete the expired items in list
    for(auto &i : position) {
        list.erase(list.begin() + i);
    }

    vector<int> position2 = {};
    //Find expired items in bidderlist
    for(int i = 0; i < (int) bidderList.size(); i++) {
        //Extract each date & time element
        std::stringstream ss1(bidderList[i].getEndTime());
        string month, day, year, hour;
        getline(ss1, month, '/');
        getline(ss1, day, '/');
        getline(ss1, year, '/');
        getline(ss1, hour, '/');

        //Conver to int
        int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

        //If end time is bigger than current time, save the position index of that item
        if(getCurrentTime() > getEndTime_sec(iMonth, iDay, iYear, iHour)) position2.push_back(i);
    }

    //Delete the expired items in bidderlist
    for(auto &i : position2) {
        bidderList.erase(bidderList.begin() + i);
    }
}

void Bidding::ratingSeller(LoginSystem &LoginSystem, string username){
    vector<int> rateSeller_Index;
    vector<string> itemName;
    vector<string> sellerName;
    vector<string> endTime;
    if(winnerList.empty()){
        cout << "\nThere is no seller to rate\n";
        return;
    }
    for(int i = 0; i < winnerList.size(); i++){
        if(winnerList[i].winnerName == username && !winnerList[i].buyer_rate_seller){
            rateSeller_Index.push_back(i);
            itemName.push_back(winnerList[i].itemName);
            sellerName.push_back(winnerList[i].sellerName);
            endTime.push_back(winnerList[i].endTime);
        }
    }

    if(sellerName.empty()){
        cout << "\nThere is no seller to rate\n";
        return;
    }
    else {
        // print out list of available seller
        cout << "\nSellers, items and end time you bid from:\n";
        for(int i = 0; i < sellerName.size(); i++){
            cout << sellerName[i] << " - " << itemName[i] << " - "  << endTime[i] << endl;
            cout << endl; // for format clearance      
        }
        // Ask for seller name to rate
        string inputSellername, inputItemname, inputEndtime;
        cout << "Enter seller name you want to rate: ";
        getline(cin, inputSellername);
        cout << "Enter item name you bid from " << inputSellername << ": ";
        getline(cin, inputItemname);
        cout << "Enter end time of " << inputItemname << ": ";
        getline(cin, inputEndtime);

        bool hasOrdered = false;
        // check the bid list
            for(int i = 0; i < sellerName.size(); i++){
                if(sellerName[i] == inputSellername && itemName[i] == inputItemname && endTime[i] == inputEndtime) {
                    hasOrdered = true;
                    for(auto &k : winnerList){
                        if(sellerName[i] == k.sellerName && k.itemName == itemName[i] && k.endTime == endTime[i]){
                            k.buyer_rate_seller = true;
                        }
                    }
                   
                }
            }

        // Check if all inputs are in the list, or type "EXIT" to exit
        while(!hasOrdered){
            cout << "The item \"" << inputItemname <<"\" you bid from \"" 
                 << inputSellername << "\", end at \"" 
                 << inputEndtime << "\" is not in your bid list\n";

            cout << "Enter the seller name again (or enter \"EXIT\" to exit): ";
            getline(cin,inputSellername);
            if(inputSellername == "EXIT") return;

            cout << "Enter item name you bid from " << inputSellername << ": ";
            getline(cin, inputItemname);
            cout << "Enter end time of " << inputItemname << ": ";
            getline(cin, inputEndtime);
            
            // check the bid list
            for(int i = 0; i < sellerName.size(); i++){
                if(sellerName[i] == inputSellername && itemName[i] == inputItemname && endTime[i] == inputEndtime) {
                    hasOrdered = true;
                    for(auto &k : winnerList){
                        if(sellerName[i] == k.sellerName && k.itemName == itemName[i] && k.endTime == endTime[i]){
                            k.buyer_rate_seller = true;
                        }
                    }
                }
            }
        }

        //rate the seller
        if(hasOrdered){
            string rate;
            cout << "Enter your rate to the " << inputSellername << ": "; getline(cin,rate);
            while(!isValid_MinBuyer(rate)) {
                cout << "Invalid rate, enter your rate again: ";
                getline(cin,rate);
            }
            int iRate = stoi(rate);
            LoginSystem.SetSellerRating(inputSellername, iRate);
        }
    }
}

void Bidding::ratingBuyer(LoginSystem &LoginSystem, string username){
    vector<int> rateBuyer_Index;
    vector<string> itemName;
    vector<string> buyerName;
    vector<string> endTime;
    if(winnerList.empty()){
        cout << "\nThere is no seller to rate\n";
        return;
    }
    for(int i = 0; i < winnerList.size(); i++){
        if(winnerList[i].sellerName == username && !winnerList[i].seller_rate_buyer){
            rateBuyer_Index.push_back(i);
            itemName.push_back(winnerList[i].itemName);
            buyerName.push_back(winnerList[i].winnerName);
            endTime.push_back(winnerList[i].endTime);
        }
    }

    if(buyerName.empty()){
        cout << "\nThere is no buyer to rate\n";
        return;
    }
    else {
        // print out list of available seller
        cout << "\nBuyers, items and end time you bid from:\n";
        for(int i = 0; i < buyerName.size(); i++){
            cout << buyerName[i] << " - " << itemName[i] << " - "  << endTime[i] << endl;
            cout << endl; // for format clearance      
        }
        // Ask for seller name to rate
        string inputBuyername, inputItemname, inputEndtime;
        cout << "Enter buyer name you want to rate: ";
        getline(cin, inputBuyername);
        cout << "Enter item name "<<  inputBuyername << " bid from you: ";
        getline(cin, inputItemname);
        cout << "Enter end time of " << inputItemname << ": ";
        getline(cin, inputEndtime);

        // Check if all inputs are in the list, or type "EXIT" to exit
        bool hasOrdered = false;

        // check the bid list
        for(int i = 0; i < buyerName.size(); i++){
            if(buyerName[i] == inputBuyername && itemName[i] == inputItemname && endTime[i] == inputEndtime) {
                hasOrdered = true;
                for(auto &k : winnerList){
                    if(inputBuyername == k.winnerName && k.itemName == inputItemname && k.endTime == inputEndtime){
                        k.seller_rate_buyer = true;
                    }
                }
            }
        }

        while(!hasOrdered){
            // check the bid list
            cout << "The item \"" << inputItemname <<"\" you bid from \"" 
                 << inputBuyername << "\", end at \"" 
                 << inputEndtime << "\" is not in your bid list\n";

            cout << "Enter the buyer name again (or enter \"EXIT\" to exit): ";
            getline(cin,inputBuyername);
            if(inputBuyername == "EXIT") return;

            cout << "Enter item name "<<  inputBuyername << " bid from you: ";
            getline(cin, inputItemname);
            cout << "Enter end time of " << inputItemname << ": ";
            getline(cin, inputEndtime);
            
            // check the bid list
            for(int i = 0; i < buyerName.size(); i++){
                if(buyerName[i] == inputBuyername && itemName[i] == inputItemname && endTime[i] == inputEndtime) {
                    hasOrdered = true;
                    for(auto &k : winnerList){
                        if(inputBuyername == k.winnerName && k.itemName == inputItemname && k.endTime == inputEndtime){
                            k.seller_rate_buyer = true;
                        }
                    }
                }
            }
        }

        //rate the buyer
        if(hasOrdered){
            string rate;
            cout << "Enter your rate to the " << inputBuyername << ": "; getline(cin,rate);
            while(!isValid_MinBuyer(rate)) {
                cout << "Invalid rate, enter your rate again: ";
                getline(cin,rate);
            }
            int iRate = stoi(rate);
            LoginSystem.SetBuyerRating(inputBuyername, iRate);
        }
    }
}


