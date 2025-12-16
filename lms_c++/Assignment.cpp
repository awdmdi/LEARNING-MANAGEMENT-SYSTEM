#include "Assignment.h"

Assignment::Assignment(const string& t)
    : title(t), count(0) {
}

void Assignment::addStudent(int id) {
    if (count >= MAX_STUDENTS) return;
    studentID[count] = id;
    marks[count++] = -1;
}

void Assignment::grade(int id, int m) {
    for (int i = 0; i < count; i++)
        if (studentID[i] == id)
            marks[i] = m;
}

void Assignment::show() const {
    cout << "  Assignment: " << title << "\n";
    for (int i = 0; i < count; i++)
        cout << "    StudentID: " << studentID[i]
        << " Marks: " << (marks[i] == -1 ? 0 : marks[i]) << "\n";
}
