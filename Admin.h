/* Header file:  
*  Only contain declarations (prototypes) 
*  of classes/ functions/ user defined data types
*/
#ifndef _ADMIN_H_     
#define _ADMIN_H_

#include <iostream>
#include <string>
#include "Member.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

class LoginAdmin : public Login {
    public:
        //Default constructor
        LoginAdmin();

        bool checkUsername(string &username);
        bool checkPassword(string &password);
};

#endif