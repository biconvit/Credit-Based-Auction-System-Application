/* Header file:  
*  Only contain declarations (prototypes) 
*  of classes/ functions/ user defined data types
*/
#ifndef _MEMBER_H_     
#define _MEMBER_H_


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "Data.h"
#include "Functions.h"

using std::string;
using std::vector;
using std::fstream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::sort;

#define LOGINFILE "LoginInfo.dat"
#define MEMBERFILE "MemberInfo.dat"

class Login {
    private: //Private
        //Attributes
        string username;
        string password;
        
    public: //Public
        Login(string username, string password);
        //Getter
        string getUsername();
        string getPwd();

        //Setter
        void setPwd(string password);

        //Display
        string display();

};



class MemberInfo {
    private: //Private
        string fullName;
        string phoneNumber;
        string email;
        string ID_type; //1 = citizen ID, 2 = passport
        string ID;
        int CP;
        double buyer_rating_score;
        double seller_rating_score;
        int number_rated_buyer;
        int number_rated_seller;
    public: //Public
        MemberInfo(string fullName, string phoneNumber, string email,
        string ID_type, string ID, int CP, double buyer_rating_score, double seller_rating_score, int number_rated_buyer, int number_rated_seller);
        
        //Getter
        int getCP();
        double getBuyerRating();
        double getSellerRating();

        //Setter
        void setFullName(string fullName);
        void setPhoneNum(string phoneNumber);
        void setEmail(string email);
        void setID_type(string ID_type);
        void setID(string ID);
        void setCP(int CP);
        void setBuyerRating(int buyer_rating_score);
        void setSellerRating(int seller_rating_score);

        //Display
        string display();
        void terminalDisplay();

};

class LoginSystem {
    private: //Private
        vector<Login> loginInfos;
        vector<MemberInfo> memberInfos;
    public: //Public
        //Constructor
        LoginSystem(vector<Login> loginInfos = {}, vector<MemberInfo> memberInfos = {});
        
        //Load and save data from .dat files
        void loadLoginData();
        void saveLoginData();
        void loadMemberData();
        void saveMemberData();

        //Other methods
        int findUser(string username);
        void registerUser(string username);
        bool comparePwd(int userID);
        short Memberview(int indUser);
        short usernameList();
        string adminDisplay(short indUser);
        
        //Getter
        double getRating(int userID);
        string getUsername(int userID);

        //Display
        int displayCP(int ID);

        //Set
        void PayBackCP(string username, int bidValue);
        void PayForBid(string username, int bidValue);
        void SetSellerRating(string sellerName, int rate);
        void SetBuyerRating(string buyerName, int rate);

        friend class LoginAdmin;
        friend class Bidding;
};

#endif