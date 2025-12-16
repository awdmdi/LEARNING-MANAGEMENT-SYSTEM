#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    Student(int, const string&, const string&, const string&);
    void menu(LMSDatabase&);
};

#endif
