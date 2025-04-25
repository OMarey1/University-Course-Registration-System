QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    admindashboard.cpp \
    banner.cpp \
    ccpage.cpp \
    cmpage.cpp \
    course.cpp \
    crpage.cpp \
    dashboard.cpp \
    instructor.cpp \
    main.cpp \
    loginpage.cpp \
    reportspage.cpp \
    student.cpp \
    user.cpp

HEADERS += \
    admin.h \
    admindashboard.h \
    banner.h \
    ccpage.h \
    cmpage.h \
    course.h \
    crpage.h \
    dashboard.h \
    instructor.h \
    loginpage.h \
    reportspage.h \
    student.h \
    user.h

FORMS += \
    admindashboard.ui \
    ccpage.ui \
    cmpage.ui \
    crpage.ui \
    dashboard.ui \
    loginpage.ui \
    reportspage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
