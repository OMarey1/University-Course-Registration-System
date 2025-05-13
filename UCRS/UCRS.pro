QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
   Sources/admin.cpp \
    Sources/admindashboard.cpp \
    Sources/banner.cpp \
    Sources/ccpage.cpp \
    Sources/cmpage.cpp \
    Sources/course.cpp \
    Sources/crpage.cpp \
    Sources/cupage.cpp \
    Sources/dashboard.cpp \
    Sources/eupage.cpp \
    Sources/instructor.cpp \
    Sources/main.cpp \
    Sources/loginpage.cpp \
    Sources/reportspage.cpp \
    Sources/student.cpp \
    Sources/user.cpp

HEADERS += \
    Headers/admin.h \
    Headers/admindashboard.h \
    Headers/banner.h \
    Headers/ccpage.h \
    Headers/cmpage.h \
    Headers/course.h \
    Headers/crpage.h \
    Headers/cupage.h \
    Headers/dashboard.h \
    Headers/eupage.h \
    Headers/instructor.h \
    Headers/loginpage.h \
    Headers/messages.h \
    Headers/reportspage.h \
    Headers/student.h \
    Headers/user.h

FORMS += \
    Forms/admindashboard.ui \
    Forms/ccpage.ui \
    Forms/cmpage.ui \
    Forms/crpage.ui \
    Forms/cupage.ui \
    Forms/dashboard.ui \
    Forms/eupage.ui \
    Forms/loginpage.ui \
    Forms/reportspage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
