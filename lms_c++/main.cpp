#include "LMSDatabase.h"
#include "Admin.h"
#include "Student.h"
#include "Teacher.h"
#include "Validation.h"
#include <iostream>
#include <exception>

int main() {
    LMSDatabase db;

    if (!db.login("admin", "admin123"))
        db.addUser(new Admin(0, "Admin", "admin", "admin123"));

    while (true) {
        try {
            int ch;
            cout << "\n1.Register 2.Login 0.Exit: ";
            cin >> ch;
            if (ch == 0) break;

            if (ch == 1) {
                int role;
                cout << "1.Student 2.Teacher: ";
                cin >> role;
                cin.ignore();

                string n, u, p;
                cout << "Name: "; getline(cin, n);
                cout << "Username: "; cin >> u;
                cout << "Password: "; cin >> p;

                if (!isStrongPassword(p))
                    throw runtime_error("Weak password");

                if (role == 1) {
                    if (!isValidRoll(u))
                        throw runtime_error("Invalid roll");
                    db.addUser(new Student(db.generateID(), n, u, p));
                }
                else {
                    if (!isValidGmail(u))
                        throw runtime_error("Invalid Gmail");
                    db.addUser(new Teacher(db.generateID(), n, u, p));
                }
            }
            else if (ch == 2) {
                string u, p;
                cout << "Username: "; cin >> u;
                cout << "Password: "; cin >> p;

                User* usr = db.login(u, p);
                if (!usr)
                    throw runtime_error("Invalid login");

                usr->menu(db);
            }
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
