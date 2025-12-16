#include "Admin.h"
#include "LMSDatabase.h"
#include <iostream>

Admin::Admin(int i, const string& n,
    const string& u, const string& p)
    : User(i, n, u, p, "admin") {
}

void Admin::menu(LMSDatabase& db) {
    int ch;
    cout << "\n1.Add Course\n2.Delete User\nChoice: ";
    cin >> ch;

    if (ch == 1) {
        string cname;
        int tid;

        cout << "Course name: ";
        cin >> cname;
        cout << "Teacher ID: ";
        cin >> tid;

        db.addCourse(cname);
        db.getCourse(db.getCourseCount() - 1)->assignTeacher(tid);
        db.saveCourses();

        cout << "Course added successfully.\n";
    }
    else if (ch == 2) {
        int uid;
        cout << "User ID to delete: ";
        cin >> uid;
        db.deleteUser(uid);
        cout << "User deleted.\n";
    }
}
