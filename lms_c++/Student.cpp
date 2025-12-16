#include "Student.h"
#include "LMSDatabase.h"
#include <iostream>

Student::Student(int i, const string& n,
    const string& u, const string& p)
    : User(i, n, u, p, "student") {
}

void Student::menu(LMSDatabase& db) {
    cout << "Available Courses:\n";
    for (int i = 0; i < db.getCourseCount(); i++)
        cout << i << ". " << db.getCourse(i)->getName() << "\n";

    int c;
    cout << "Enroll index: ";
    cin >> c;
    if (db.getCourse(c))
        db.getCourse(c)->enrollStudent(id);
}
