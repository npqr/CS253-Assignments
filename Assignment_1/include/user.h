#ifndef USER_H
#define USER_H

//// User Class                  //////////////////////////////////////

#include <string>
using namespace std;

class User {
private:
    string name;
    string ID;
    string password;

public:
    User(const string& name, string ID, const string& password)
        : name(name), ID(ID), password(password) {}

    string getName() const { return name; }
    string getID() const { return ID; }
    string getPassword() const { return password; }
    
};

#endif // USER_H