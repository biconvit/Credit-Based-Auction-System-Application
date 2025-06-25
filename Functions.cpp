#include "Functions.h"

//For LoginSystem class
string askUsername() {
        //Prompt the user to enter username
        string username;
        cout << "Username could not contain white space!\n";
        cout << "Enter username: ";
        getline(cin, username);

        //Check white space
        while(1) { //Check for white space until there is no white space in the username
        bool isWS = false; //white space flag
        for(int i = 0; i < (int) username.length(); i++) { //Find white space
                if(isspace(username[i])) isWS = true;
        }

        if(isWS == false) break;
        else { //Prompt user to enter again
                cout <<"There is a white space, please enter again: ";
                getline(cin, username);
        }
        }

        return username;
}

bool isValidName(string name) {
        //If name has other characters except alpha characters, return false
        for(int i = 0; i < name.length(); i++) 
                if(!std::isalpha(name[i]) && !std::isblank(name[i])) return false;
        
        return true;
}

bool isValidPhoneNumber(string number) {
        //If phone number contains other characters except digits, return false
        for(int i = 0; i < number.length(); i++) 
                if(!std::isdigit(number[i])) return false;

        return true;
}

bool isValidEmail(string email) {
        //If email does not contain '@' or '.', return false
        if(email.find('@') == string::npos || email.find('.') == string::npos) return false;

        return true;
}

bool isValidID(string ID_type, string ID) {
        /*Citizen ID and Passport are based on the format of Vietnam. Citizen ID contains only number
        where the passport has an uppercase letter in the first character and the remainings are number only*/
        if(ID_type == "1"){ // Citizen ID
                for(int i = 0; i < ID.length(); i++){
                        if(ID[i] < 48 || ID[i] > 57){ // check that ID only contain number
                                return false;
                        }
                }
        }
        else if(ID_type == "2"){ // Passport  
                for(int i = 1; i < ID.length(); i++){ //Check the first character is UPPERCASE letter
                        if(ID[0] < 65 || ID[0] > 90)
                        {
                                return false;
                        }
                        if(ID[i] < 48 || ID[i] > 57){  //Check that the rest are numbers only
                                return false;
                        }
                }
        }
        return true;
}

bool isWeakPwd(string password) {
        bool lowerChar = false, upperChar = false, digitChar = false, specialChar = false;

        //Loop through password to check the requirements
        for(int i = 0; i < password.length(); i++) {
                if(std::islower(password[i])) lowerChar = true; //Have lowercase
                else if(std::isupper(password[i])) upperChar = true; //Have uppercase
                else if(std::isdigit(password[i])) digitChar = true; //Have digit
                else if(std::ispunct(password[i])) specialChar = true; //Have special character
                else if(std::isspace(password[i])) {
                        cout << "Password cannot have space!\n";
                        return false;
                }
        }

        //If statisfy all the requirements, return true
        if (lowerChar && upperChar && digitChar && specialChar && (password.length() >= 8)) return true;
        //Does not satisfy all requirements, prompt user the cause and return false
        else cout << "Password must have more than 8 characters and must contain lowercase, uppercase, number and special characters\n";

        return false;
}

//Bidding class
bool isValid_ItemName(const string& itemName) {
    if(itemName.size() > 30) {
        cout << "Item's name must be smaller than 30 characters\n";
        return false; // Item name exceeds 15 characters
    }

    int alnum = 0;
    for(char c : itemName) {
        //Check if there is any alphanumeric in the item name
        if(isalnum(c)) alnum++;

        //Only alphanumeric and blank is allowed
        if(!isalnum(c) && !isblank(c)) {
            cout << "Only alphanumerics and blanks are allowed!\n";
            return false; // Contains invalid characters
        }
    }

    //Item name contains only blank
    if(alnum == 0) return false;

    return true; // Valid item name
}

bool isValid_Category(string& category) {
    //toupper the first char of the string and tolower others
    for(int i = 0; i < (int) category.size(); i++) {
        if(i != 0) category[i] = std::tolower(category[i]);
        else category[i] = std::toupper(category[i]);
    }

    //Three categories
    return (category == "Weapon" || category == "Figure" || category == "Electronics");
}

bool isValid_Description(const string& description) {
    if (description.size() > 150) {
        cout << "Item's name must be smaller than 150 characters\n";
        return false; // Description exceeds 150 characters
    }

    for (char c : description) {
        if (!isalnum(c) && !isblank(c)) {
            cout << "Only alphanumerics and blanks are allowed!\n";
            return false; // Contains invalid characters
        }
    }

    return true; // Valid description
}

bool is_Int_notNegative(const string& value) {
    //Only integer is allowed
    for(int i = 0; i < (int) value.size(); i++) 
        if(!isdigit(value[i])) return false;

    //Value cannot be negative
    if(std::stoi(value) < 0) return false;

    return true; // Valid
}

bool isValid_MinBuyer(const string& minBuyer_score){
    //Only integer is allowed
    for(int i = 0; i < (int) minBuyer_score.size(); i++) 
        if(!isdigit(minBuyer_score[i])) return false;

    //Value cannot be negative
    if(std::stoi(minBuyer_score) < 0 || std::stoi(minBuyer_score) > 5) return false;

    return true; // Valid minimum buyer score 
}

long long getCurrentTime() {
    //Current time
    time_t now = time(NULL);
    return now;
}
    
//MM/DD/YYYY/HH
bool isNum(string endTimeData){
    if (endTimeData.empty()) return false;
    for (char &i : endTimeData){
        if(!isdigit(i)) return false;
    }
    return true;
}

long long getEndTime_sec(int month, int day, int year, int hour) { //return seconds from 1970
    //End Time
    struct tm Endtime_info = {};
    //Increase to end time
    Endtime_info.tm_hour = hour;
    Endtime_info.tm_mday = day;
    Endtime_info.tm_mon = (month -1); // range of month is 0-11
    Endtime_info.tm_year = year - 1900;
    //Make new time
    time_t new_time = mktime(&Endtime_info); // since Epoch
    if(new_time == -1){
        std::cerr <<"\n Fail to convert time \n";
        return -1;
    }
    return new_time;
}

bool isValidEndTime(string endTime) {
    //Extract each date & time element
    std::stringstream ss(endTime);
    string month, day, year, hour;
    getline(ss, month, '/');
    getline(ss, day, '/');
    getline(ss, year, '/');
    getline(ss, hour, '/');

    //Check for invalid character
    if(!isNum(month) || !isNum(day) || !isNum(year) || !isNum(hour)) {
        cout << "Contain invalid character or empty\n";
        return false;
    }

    int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

    //Check for valid month
    if((iMonth < 1 || iMonth > 12)) {
        cout << "Invalid month\n";
        return false;
    }

    //Check for valid hour
    if((iHour < 0 || iHour > 23)){
        cout << "Invalid hour\n";
        return false;
    } 

    //Check for leap year
    bool isLeapYear = false;
    if((iYear % 4 == 0 && iYear % 100 != 0) || iYear % 400 == 0) isLeapYear = true;

    //Check for day
    const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int maxDays = (iMonth == 2 && isLeapYear) ? 29 : daysInMonth[iMonth - 1];
    if(iDay < 1 || iDay > maxDays){
        cout << "Invalid day\n"; 
        return false;
    }

    //Check valid end time
    //Current time
    time_t now = time(NULL);
    
    if(getEndTime_sec(iMonth, iDay, iYear, iHour) - now < 0) {
        cout << "Given end time is in the past\n";
        return false;
    }

    // All are valid
    return true;
}

string getFormattedEndTime(string endTime) {
    //Extract each date & time element
    std::stringstream ss(endTime);
    string month, day, year, hour;
    getline(ss, month, '/');
    getline(ss, day, '/');
    getline(ss, year, '/');
    getline(ss, hour, '/');

    int iMonth = std::stoi(month), iDay = std::stoi(day), iYear = std::stoi(year), iHour = std::stoi(hour);

    time_t end = getEndTime_sec(iMonth, iDay, iYear, iHour);

    struct tm* end_time = localtime(&end);
    char buffer[80];

    //Save formatted time into buffer
    strftime(buffer, 80, "%m/%d/%Y %H:%M", end_time);
    return buffer;
}

bool isBidValueValid(int bidValue,int CP, int highestBid, int increment, int start){ // enough CP, sastisfy increment, bigger or equal start bid
    //bigger or equal start bid
    if(bidValue < start) {
        cout << "Your bid must be bigger than the start bid\n";
        return false;
    }

    //Enough CP
    if(bidValue > CP){
        cout << "Do not have enough credit point\n";
        return false;
    }
    // Satisfy increment
    if(bidValue - highestBid < increment){
        cout << "Your bid does not meet the increment\n";
        return false;
    }

    return true;
}

bool isValid_SearchCategory(string& searchCategory) {
    //toupper the first char of the string and tolower others
    for(int j = 0; j < (int) searchCategory.size(); j++) {
        if(j != 0) searchCategory[j] = std::tolower(searchCategory[j]);
        else searchCategory[j] = std::toupper(searchCategory[j]);
    }

   // Three categories
    if(searchCategory == "Weapon" || searchCategory == "Figure" || searchCategory == "Electronics"){
         return true;
    }else{
        return false;
    }
}

bool isValid_inputCreditPoint(const string& Creditpoits) {
    if(Creditpoits.size() > 15) {
        return false; // Item name exceeds 15 characters
    }

    int alnum = 0;
    for(char c : Creditpoits) {
        //Check if there is any alphanumeric in the item name
        if(isalnum(c)) alnum++;

        //Only alphanumeric and blank is allowed
        if(!isalnum(c) && !isblank(c)) {
            return false; // Contains invalid characters
        }
    }

    //Item name contains only blank
    if(alnum == 0) return false;

    return true; // Valid item name
}