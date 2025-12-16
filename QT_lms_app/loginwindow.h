#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "lmsdatabase.h" // Include the core logic
#include "dashboard.h"   // Include the dashboard

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    Dashboard *dashboard = nullptr;
};

#endif // LOGINWINDOW_H
