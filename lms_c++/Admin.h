#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class LMSDatabase;

class Admin : public User {
public:
    Admin(int, const string&, const string&, const string&);
    void menu(LMSDatabase&);
};

#endif
