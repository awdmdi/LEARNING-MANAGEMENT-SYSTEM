#include "LMSDatabase.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

LMSDatabase::LMSDatabase()
    : userCount(0), courseCount(0), nextID(1) {
    loadUsers();
    loadCourses();
}

LMSDatabase::~LMSDatabase() {
    for (int i = 0; i < userCount; i++)
        delete users[i];
}

int LMSDatabase::generateID() {
    return nextID++;
}

void LMSDatabase::addUser(User* u) {
    if (userCount < MAX_USERS) {
        users[userCount++] = u;
        saveUsers();
    }
}

void LMSDatabase::deleteUser(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getID() == id) {
            delete users[i];
            for (int j = i; j < userCount - 1; j++)
                users[j] = users[j + 1];
            userCount--;
            saveUsers();
            return;
        }
    }
}

User* LMSDatabase::login(const string& u, const string& p) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUsername() == u &&
            users[i]->verifyPassword(p))
            return users[i];
    }
    return NULL;
}

int LMSDatabase::getCourseCount() const {
    return courseCount;
}

Course* LMSDatabase::getCourse(int i) {
    if (i >= 0 && i < courseCount)
        return &courses[i];
    return NULL;
}

void LMSDatabase::addCourse(const string& n) {
    if (courseCount < MAX_COURSES) {
        courses[courseCount++] = Course(n);
        saveCourses();
    }
}

void LMSDatabase::saveUsers() const {
    ofstream fout("users.txt");
    for (int i = 0; i < userCount; i++)
        users[i]->save(fout);
}

void LMSDatabase::saveCourses() const {
    ofstream fout("courses.txt");
    for (int i = 0; i < courseCount; i++)
        courses[i].save(fout);
}

void LMSDatabase::loadUsers() {
    ifstream fin("users.txt");
    if (!fin) return;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string idStr, role, name, uname, pass;

        getline(ss, idStr, '|');
        getline(ss, role, '|');
        getline(ss, name, '|');
        getline(ss, uname, '|');
        getline(ss, pass, '|');

        int id = atoi(idStr.c_str());
        nextID = max(nextID, id + 1);

        if (role == "admin")
            users[userCount++] = new Admin(id, name, uname, pass);
        else if (role == "teacher")
            users[userCount++] = new Teacher(id, name, uname, pass);
        else if (role == "student")
            users[userCount++] = new Student(id, name, uname, pass);
    }
}

void LMSDatabase::loadCourses() {
    ifstream fin("courses.txt");
    if (!fin) return;

    string line;
    while (getline(fin, line) && courseCount < MAX_COURSES) {
        courses[courseCount++].load(line);
    }
}
