#ifndef LMSDATABASE_H
#define LMSDATABASE_H

#include "User.h"
#include "Course.h"

const int MAX_USERS = 50;
const int MAX_COURSES = 10;

class LMSDatabase {
    User* users[MAX_USERS];
    int userCount;
    Course courses[MAX_COURSES];
    int courseCount;
    int nextID;

public:
    LMSDatabase();
    ~LMSDatabase();

    int generateID();
    void addUser(User*);
    void deleteUser(int);
    User* login(const string&, const string&);

    int getCourseCount() const;
    Course* getCourse(int);

    void addCourse(const string&);
    void saveUsers() const;
    void saveCourses() const;
    void loadUsers();
    void loadCourses();
};

#endif
