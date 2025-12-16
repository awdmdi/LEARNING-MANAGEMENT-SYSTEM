#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include <iostream>
using namespace std;

const int MAX_STUDENTS = 50;

class Assignment {
    string title;
    int studentID[MAX_STUDENTS];
    int marks[MAX_STUDENTS];
    int count;

public:
    Assignment(const string & = "");
    void addStudent(int);
    void grade(int, int);
    void show() const;
};

#endif
