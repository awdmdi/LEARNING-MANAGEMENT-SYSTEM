#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "lmsdatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dashboard; }
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(User* loggedInUser, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_logoutButton_clicked();
    void on_deleteUserButton_clicked();
    void on_addCourseButton_clicked();
    void populateUserList(); // Utility to refresh user list for admin

private:
    Ui::Dashboard *ui;
    User* currentUser;

    void setupDashboardByRole(); // Sets up visibility based on role
};

#endif // DASHBOARD_H
