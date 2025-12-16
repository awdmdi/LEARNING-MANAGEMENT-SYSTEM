#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QInputDialog>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    // Optional: Set up the initial look
    setWindowTitle("LMS Login");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Convert QString to std::string for the core logic
    std::string u = username.toStdString();
    std::string p = password.toStdString();

    LoginResult result = LMSDatabase::getInstance().login(u, p);

    if (result.user) {
        // Successful Login
        QMessageBox::information(this, "Success", QString("Welcome, %1!").arg(QString::fromStdString(result.user->getName())));

        // Open the Dashboard
        if (dashboard) delete dashboard; // Clean up previous
        dashboard = new Dashboard(result.user, this);
        dashboard->show();
        this->hide(); // Hide the login window
    } else {
        // Failed Login
        QMessageBox::critical(this, "Login Failed", QString::fromStdString(result.message));
    }
}

void LoginWindow::on_registerButton_clicked()
{
    // A simple, sequential registration form using QInputDialog for simplicity
    QString name = QInputDialog::getText(this, "Register User", "Enter Name:");
    if (name.isEmpty()) return;

    QString username = QInputDialog::getText(this, "Register User", "Enter Username (Roll/Gmail):");
    if (username.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Register User", "Enter Password:", QLineEdit::Password);
    if (password.isEmpty()) return;

    QStringList roles;
    roles << "Student" << "Teacher";
    QString roleStr = QInputDialog::getItem(this, "Register User", "Select Role:", roles, 0, false);
    if (roleStr.isEmpty()) return;

    std::string role = roleStr.toLower().toStdString();

    // Call the core logic's addUser function
    std::string error = LMSDatabase::getInstance().addUser(
        name.toStdString(),
        username.toStdString(),
        password.toStdString(),
        role
    );

    if (error.empty()) {
        QMessageBox::information(this, "Registration Successful", "You can now log in.");
    } else {
        QMessageBox::critical(this, "Registration Failed", QString::fromStdString(error));
    }
}
