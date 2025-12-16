#include "Course.h"
#include <fstream>     
#include <sstream>
#include <cstdlib>
#include <iostream>


Course::Course(const string& n)
    : name(n), teacherID(-1), studentCount(0), assignmentCount(0) {
}

string Course::getName() const { return name; }
int Course::getTeacherID() const { return teacherID; }

void Course::assignTeacher(int id) {
    teacherID = id;
}

void Course::enrollStudent(int id) {
    if (studentCount >= MAX_STUDENTS) return;
    students[studentCount++] = id;
    for (int i = 0; i < assignmentCount; i++)
        assignments[i].addStudent(id);
}

void Course::addAssignment(const string& t) {
    if (assignmentCount >= MAX_ASSIGNMENTS) return;
    assignments[assignmentCount] = Assignment(t);
    for (int i = 0; i < studentCount; i++)
        assignments[assignmentCount].addStudent(students[i]);
    assignmentCount++;
}

void Course::show() const {
    cout << "Course: " << name << "\n";
    for (int i = 0; i < assignmentCount; i++)
        assignments[i].show();
}

void Course::save(ofstream& fout) const {
    fout << name << "|" << teacherID << "\n";
}

void Course::load(const string& line) {
    stringstream ss(line);
    string tid;
    getline(ss, name, '|');
    getline(ss, tid, '|');
    teacherID = atoi(tid.c_str());
}
