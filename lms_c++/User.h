#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
using namespace std;

class LMSDatabase;

class User {
protected:
    int id;
    string name, username, password, role;

public:
    User(int, const string&, const string&, const string&, const string&);
    virtual ~User();

    int getID() const;
    string getName() const;
    string getUsername() const;
    string getRole() const;

    bool verifyPassword(const string&) const;
    void save(ofstream&) const;

    virtual void menu(LMSDatabase&) = 0;
};

#endif
