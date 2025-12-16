#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"

class LMSDatabase;

class Teacher : public User {
public:
    Teacher(int, const string&, const string&, const string&);
    void menu(LMSDatabase&);
};

#endif
