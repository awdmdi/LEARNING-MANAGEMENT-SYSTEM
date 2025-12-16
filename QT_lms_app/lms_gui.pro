QT += widgets

CONFIG += c++11

# The files provided by the user (combined into lmsdatabase.h/cpp)
HEADERS += lmsdatabase.h \
           loginwindow.h \
           dashboard.h

SOURCES += main.cpp \
           lmsdatabase.cpp \
           loginwindow.cpp \
           dashboard.cpp

FORMS += loginwindow.ui \
         dashboard.ui

# Optional: Set the application name
TARGET = LMS_GUI
# lms_gui.pro

# ... (Existing lines like QT += widgets and FORMS += ...)

# **ADD THIS LINE TO THE END OF YOUR .PRO FILE**
# This forces the use of forward slashes (/) for all paths generated in the Makefile,
# which fixes many MinGW/Windows path issues.
QMAKE_DIR_SEP = /

# ... (End of file)
