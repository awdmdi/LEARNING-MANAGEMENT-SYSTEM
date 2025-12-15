#include "dashboard.h"
#include "ui_dashboard.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QInputDialog>

Dashboard::Dashboard(User* loggedInUser, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
    , currentUser(loggedInUser)
{
    ui->setupUi(this);
    setWindowTitle("LMS Dashboard");

    QString welcomeText = QString("Welcome, %1 (%2) - ID: %3")
                              .arg(QString::fromStdString(currentUser->getName()))
                              .arg(QString::fromStdString(currentUser->getRole()))
                              .arg(currentUser->getID());

    ui->welcomeLabel->setText(welcomeText);

    setupDashboardByRole();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setupDashboardByRole()
{
    QString role = QString::fromStdString(currentUser->getRole());

    if (role == "admin") {
        ui->mainTabs->setTabVisible(0, true); // Admin tab is the first (index 0)
        populateUserList();
    } else {
        ui->mainTabs->setTabVisible(0, false);
    }
    // TODO: Add Teacher/Student tabs setup logic here
}

void Dashboard::populateUserList()
{
    ui->userListCombo->clear();
    LMSDatabase& db = LMSDatabase::getInstance();

    for (int i = 0; i < db.getUserCount(); ++i) {
        User* user = db.getUser(i);
        if (user && user->getRole() != "admin") { // Admins can't delete other admins
            QString item = QString("[%1] %2 (%3)").arg(user->getID()).arg(QString::fromStdString(user->getName())).arg(QString::fromStdString(user->getRole()));
            ui->userListCombo->addItem(item, QVariant(user->getID())); // Store ID in the item's data
        }
    }
}

void Dashboard::on_logoutButton_clicked()
{
    // Safely cast the parent back to LoginWindow and show it
    LoginWindow *login = qobject_cast<LoginWindow*>(parent());
    if (login) {
        login->show();
        this->hide();
    }
}

void Dashboard::on_deleteUserButton_clicked()
{
    int userID = ui->userListCombo->currentData().toInt();
    if (userID == 0) {
        QMessageBox::warning(this, "Error", "Please select a non-admin user to delete.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion",
                                  QString("Are you sure you want to delete user ID %1?").arg(userID),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        std::string error = LMSDatabase::getInstance().deleteUser(userID);
        if (error.empty()) {
            QMessageBox::information(this, "Success", "User deleted successfully.");
            populateUserList(); // Refresh the list
        } else {
            QMessageBox::critical(this, "Deletion Failed", QString::fromStdString(error));
        }
    }
}

void Dashboard::on_addCourseButton_clicked()
{
    QString courseName = QInputDialog::getText(this, "Add Course", "Enter Course Name:");
    if (courseName.isEmpty()) return;

    QString teacherIDStr = QInputDialog::getText(this, "Add Course", "Enter Teacher ID to Assign:");
    bool ok;
    int teacherID = teacherIDStr.toInt(&ok);

    if (ok) {
        // NOTE: In a full app, you'd validate the Teacher ID exists.
        LMSDatabase::getInstance().addCourse(courseName.toStdString(), teacherID);
        QMessageBox::information(this, "Success", "Course added and saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Invalid Teacher ID entered.");
    }
}

// TODO: Implement Teacher and Student specific slot functions
