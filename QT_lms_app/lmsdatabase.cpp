#include "lmsdatabase.h"
#include <cstdlib> // For atoi

// ===================== VALIDATION IMPLEMENTATION =====================
bool isValidRoll(const std::string& r) {
    if (r.length() != 13) return false;
    if (r.substr(0, 3) != "01-") return false;
    if (r[9] != '-') return false;
    for (int i = 3; i <= 8; i++) if (!isdigit(r[i])) return false;
    for (int i = 10; i <= 12; i++) if (!isdigit(r[i])) return false;
    return true;
}

bool isValidGmail(const std::string& g) {
    const std::string s = "@gmail.com";
    return g.length() > s.length() && g.substr(g.length() - s.length()) == s;
}

bool isStrongPassword(const std::string& p) {
    if (p.length() < 6) return false;
    for (char c : p) if (isdigit(c)) return true;
    return false;
}

// ===================== USER BASE IMPLEMENTATION =====================
User::User(int i, const std::string& n, const std::string& u, const std::string& p, const std::string& r)
    : id(i), name(n), username(u), password(p), role(r) {}

void User::save(std::ofstream& fout) const {
    fout << id << "|" << role << "|" << name << "|" << username << "|" << password << '\n';
}

// ===================== ASSIGNMENT IMPLEMENTATION =====================
Assignment::Assignment(const std::string& t) : title(t), count(0) {}

void Assignment::addStudent(int id) {
    if (count >= MAX_STUDENTS) return;
    studentID[count] = id;
    marks[count++] = -1;
}

void Assignment::grade(int id, int m) {
    for (int i = 0; i < count; i++)
        if (studentID[i] == id) marks[i] = m;
}

// ===================== COURSE IMPLEMENTATION =====================
Course::Course(const std::string& n) : name(n), teacherID(-1), studentCount(0), assignmentCount(0) {}

void Course::enrollStudent(int id) {
    if (studentCount >= MAX_STUDENTS) return;
    students[studentCount++] = id;
    for (int i = 0; i < assignmentCount; i++) assignments[i].addStudent(id);
}

void Course::addAssignment(const std::string& t) {
    if (assignmentCount >= MAX_ASSIGNMENTS) return;
    assignments[assignmentCount] = Assignment(t);
    for (int i = 0; i < studentCount; i++) assignments[assignmentCount].addStudent(students[i]);
    assignmentCount++;
}

void Course::gradeStudent(int assignIdx, int sid, int marks) {
    if (assignIdx < 0 || assignIdx >= assignmentCount) return;
    assignments[assignIdx].grade(sid, marks);
}

void Course::save(std::ofstream& fout) const {
    fout << name << "|" << teacherID << '\n';
    // TODO: Need to save student enrollments and assignments data too
    // For now, only Course name and TeacherID are saved as per original code.
}

void Course::load(const std::string& line) {
    std::stringstream ss(line);
    std::string t;
    std::getline(ss, name, '|');
    std::getline(ss, t, '|');
    teacherID = atoi(t.c_str());
}

// ===================== DATABASE IMPLEMENTATION =====================
LMSDatabase::LMSDatabase() : userCount(0), courseCount(0), nextID(1) {
    loadUsers();
    loadCourses();

    // Ensure a default Admin exists
    if (login("admin", "admin123").user == nullptr) {
        users[userCount++] = new Admin(0, "System Admin", "admin", "admin123");
        nextID = std::max(nextID, 1);
        saveUsers();
    }
}

LMSDatabase& LMSDatabase::getInstance() {
    static LMSDatabase instance; // Guaranteed to be destroyed. Instantiated on first use.
    return instance;
}

int LMSDatabase::generateID() { return nextID++; }

std::string LMSDatabase::addUser(const std::string& n, const std::string& u, const std::string& p, const std::string& role) {
    if (userCount >= MAX_USERS) return "Error: Maximum user limit reached.";

    // Check for unique username
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUsername() == u) return "Error: Username already exists.";
    }

    int newID = generateID();
    User* newUser = nullptr;

    if (role == "student") {
        if (!isValidRoll(u)) return "Error: Invalid roll number format (Expected: 01-xxxxxx-xxx).";
        newUser = new Student(newID, n, u, p);
    } else if (role == "teacher") {
        if (!isValidGmail(u)) return "Error: Invalid Gmail format (Expected: user@gmail.com).";
        newUser = new Teacher(newID, n, u, p);
    } else {
        return "Error: Invalid user role.";
    }

    if (!isStrongPassword(p)) {
        delete newUser;
        return "Error: Weak password (Must be at least 6 characters and contain a digit).";
    }

    users[userCount++] = newUser;
    saveUsers();
    return ""; // Success
}

std::string LMSDatabase::deleteUser(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getID() == id) {
            if (users[i]->getRole() == "admin") return "Error: Cannot delete an admin user.";
            delete users[i];
            for (int j = i; j < userCount - 1; j++) users[j] = users[j + 1];
            userCount--;
            saveUsers();
            return ""; // Success
        }
    }
    return "Error: User ID not found.";
}


LoginResult LMSDatabase::login(const std::string& u, const std::string& p) const {
    for (int i = 0; i < userCount; i++)
        if (users[i]->getUsername() == u && users[i]->verifyPassword(p))
            return {"", users[i]};
    return {"Invalid username or password.", nullptr};
}

Course* LMSDatabase::getCourse(int i) {
    return (i >= 0 && i < courseCount) ? &courses[i] : nullptr;
}

void LMSDatabase::addCourse(const std::string& n, int teacherID) {
    if (courseCount < MAX_COURSES) {
        courses[courseCount] = Course(n);
        courses[courseCount++].assignTeacher(teacherID);
        saveCourses();
    }
}

void LMSDatabase::saveUsers() const {
    std::ofstream fout("users.txt");
    if (!fout) return;
    for (int i = 0; i < userCount; i++) users[i]->save(fout);
}

void LMSDatabase::saveCourses() const {
    std::ofstream fout("courses.txt");
    if (!fout) return;
    for (int i = 0; i < courseCount; i++) courses[i].save(fout);
}

void LMSDatabase::loadUsers() {
    std::ifstream fin("users.txt");
    if (!fin) return;
    std::string line;
    while (std::getline(fin, line) && userCount < MAX_USERS) {
        std::stringstream ss(line);
        std::string idStr, role, name, uname, pass;
        std::getline(ss, idStr, '|');
        std::getline(ss, role, '|');
        std::getline(ss, name, '|');
        std::getline(ss, uname, '|');
        std::getline(ss, pass, '|');
        int id = atoi(idStr.c_str());
        nextID = std::max(nextID, id + 1);
        if (role == "admin") users[userCount++] = new Admin(id, name, uname, pass);
        else if (role == "teacher") users[userCount++] = new Teacher(id, name, uname, pass);
        else if (role == "student") users[userCount++] = new Student(id, name, uname, pass);
    }
}

void LMSDatabase::loadCourses() {
    std::ifstream fin("courses.txt");
    if (!fin) return;
    std::string line;
    while (std::getline(fin, line) && courseCount < MAX_COURSES)
        courses[courseCount++].load(line);
}
