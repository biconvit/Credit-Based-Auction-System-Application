#ifndef _FUNCTIONS_H_     
#define _FUNCTIONS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

using std::string;
using std::cout;
using std::cin;

//For LoginSystem class
string askUsername();
bool isValidName(string name);
bool isValidPhoneNumber(string number);
bool isValidEmail(string email);
bool isValidID(string ID_type, string ID);
bool isWeakPwd(string password);

//Bidding class
bool isValid_ItemName(const string& itemName);
bool isValid_Category(string& category);


bool isValid_Description(const string& description);
bool is_Int_notNegative(const string& value);
bool isValid_MinBuyer(const string& minBuyer_score);

//Working with start time and end time of bid item
long long getCurrentTime();
bool isNum(string endTimeData);
long long getEndTime_sec(int month, int day, int year, int hour); //return seconds from 1970
bool isValidEndTime(string endTime);
string getFormattedEndTime(string endTime);

//Working with bidding
bool isBidValueValid(int bidValue, int CP, int highestBid, int increment, int start);
//check search category
bool isValid_SearchCategory(string& searchCategory);
bool isValid_inputCreditPoint(const string& Creditpoits);

#endif