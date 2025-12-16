#ifndef LMSDATABASE_H
#define LMSDATABASE_H

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// Use a structure to safely return a User pointer and a success/error message
struct LoginResult {
    std::string message;
    class User* user = nullptr;
};

// ===================== CONSTANTS =====================
const int MAX_USERS = 50;
const int MAX_COURSES = 10;
const int MAX_STUDENTS = 50;
const int MAX_ASSIGNMENTS = 10;

// ===================== VALIDATION (Keep as is) =====================
bool isValidRoll(const std::string& r);
bool isValidGmail(const std::string& g);
bool isStrongPassword(const std::string& p);

// ===================== USER BASE =====================
class User {
protected:
    int id;
    std::string name, username, password, role;
public:
    User(int i, const std::string& n, const std::string& u, const std::string& p, const std::string& r);
    virtual ~User() {}

    int getID() const { return id; }
    std::string getName() const { return name; }
    std::string getUsername() const { return username; }
    std::string getRole() const { return role; }
    bool verifyPassword(const std::string& p) const { return p == password; }

    // Removed virtual menu()
    void save(std::ofstream& fout) const;
};

// ===================== ASSIGNMENT =====================
class Assignment {
    // ... (Keep the content of Assignment class as is, just the declaration)
    std::string title;
    int studentID[MAX_STUDENTS];
    int marks[MAX_STUDENTS];
    int count;
public:
    Assignment(const std::string& t = "");

    void addStudent(int id);
    void grade(int id, int m);
    // show() removed for GUI
};

// ===================== COURSE =====================
class Course {
    // ... (Keep the content of Course class as is, just the declaration)
    std::string name;
    int teacherID;
    int students[MAX_STUDENTS];
    int studentCount;
    Assignment assignments[MAX_ASSIGNMENTS];
    int assignmentCount;
public:
    Course(const std::string& n = "");

    std::string getName() const { return name; }
    int getTeacherID() const { return teacherID; }
    void assignTeacher(int id) { teacherID = id; }

    void enrollStudent(int id);
    void addAssignment(const std::string& t);
    void gradeStudent(int assignIdx, int sid, int marks);
    // show() removed for GUI

    void save(std::ofstream& fout) const;
    void load(const std::string& line);
    int getAssignmentCount() const { return assignmentCount; }
    // listAssignments() removed for GUI
};

// ===================== USER ROLES =====================
class Student : public User {
public:
    Student(int i, const std::string& n, const std::string& u, const std::string& p)
        : User(i, n, u, p, "student") {}
};

class Teacher : public User {
public:
    Teacher(int i, const std::string& n, const std::string& u, const std::string& p)
        : User(i, n, u, p, "teacher") {}
};

class Admin : public User {
public:
    Admin(int i, const std::string& n, const std::string& u, const std::string& p)
        : User(i, n, u, p, "admin") {}
};

// ===================== DATABASE (Centralized Logic) =====================
class LMSDatabase {
    User* users[MAX_USERS];
    int userCount;
    Course courses[MAX_COURSES];
    int courseCount;
    int nextID;

    // Private constructor for Singleton pattern (optional but good practice for a DB)
    LMSDatabase();
    // Prevent copying
    LMSDatabase(const LMSDatabase&) = delete;
    LMSDatabase& operator=(const LMSDatabase&) = delete;

public:
    static LMSDatabase& getInstance();

    int generateID();

    // Changed signature to return success status/error message
    std::string addUser(const std::string& n, const std::string& u, const std::string& p, const std::string& role);
    std::string deleteUser(int id);

    LoginResult login(const std::string& u, const std::string& p) const;

    // Getters for GUI
    int getUserCount() const { return userCount; }
    User* getUser(int i) { return (i >= 0 && i < userCount) ? users[i] : nullptr; }

    int getCourseCount() const { return courseCount; }
    Course* getCourse(int i);

    void addCourse(const std::string& n, int teacherID);

    void saveUsers() const;
    void saveCourses() const;

private:
    void loadUsers();
    void loadCourses();
};

#endif // LMSDATABASE_H
