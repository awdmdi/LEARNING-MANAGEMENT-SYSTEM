#include "Teacher.h"
#include "LMSDatabase.h"
#include <iostream>

Teacher::Teacher(int i, const string& n,
    const string& u, const string& p)
    : User(i, n, u, p, "teacher") {
}

void Teacher::menu(LMSDatabase& db) {
    int myCourses[10];
    int count = 0;

    cout << "\nYour Courses:\n";
    for (int i = 0; i < db.getCourseCount(); i++) {
        if (db.getCourse(i)->getTeacherID() == id) {
            cout << count << ". "
                << db.getCourse(i)->getName() << "\n";
            myCourses[count++] = i;
        }
    }

    if (count == 0) {
        cout << "No courses assigned.\n";
        return;
    }

    int choice = -1;
    cout << "Select course index: ";
    cin >> choice;
    if (choice < 0 || choice >= count) return;

    Course* c = db.getCourse(myCourses[choice]);

    int ch;
    cout << "\n1.Add Assignment\n2.View Course\nChoice: ";
    cin >> ch;

    if (ch == 1) {
        string title;
        cout << "Assignment title: ";
        cin.ignore();
        getline(cin, title);
        c->addAssignment(title);
        db.saveCourses();
        cout << "Assignment added.\n";
    }
    else if (ch == 2) {
        c->show();
    }
}
