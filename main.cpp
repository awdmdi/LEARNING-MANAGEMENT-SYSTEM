#include "loginwindow.h"
#include <QApplication>
#include <QFile> // Required for file loading

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // --- QSS Loading Code ---
    QFile styleFile("style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
        styleFile.close();
    }
    // ------------------------

    // Ensure the database is initialized
    LMSDatabase::getInstance();

    LoginWindow w;
    w.show();

    return a.exec();
}
