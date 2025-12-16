#include "User.h"

User::User(int i, const string& n, const string& u,
    const string& p, const string& r)
    : id(i), name(n), username(u), password(p), role(r) {
}

User::~User() {}

int User::getID() const { return id; }
string User::getName() const { return name; }
string User::getUsername() const { return username; }
string User::getRole() const { return role; }

bool User::verifyPassword(const string& p) const {
    return p == password;
}

void User::save(ofstream& fout) const {
    fout << id << "|" << role << "|" << name
        << "|" << username << "|" << password << "\n";
}
