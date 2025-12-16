#ifndef COURSE_H
#define COURSE_H

#include "Assignment.h"
#include <string>
using namespace std;

const int MAX_ASSIGNMENTS = 10;

class Course {
    string name;
    int teacherID;
    int students[MAX_STUDENTS];
    int studentCount;
    Assignment assignments[MAX_ASSIGNMENTS];
    int assignmentCount;

public:
    Course(const string & = "");

    string getName() const;
    int getTeacherID() const;

    void assignTeacher(int);
    void enrollStudent(int);
    void addAssignment(const string&);
    void show() const;

    void save(ofstream&) const;
    void load(const string&);
};

#endif
