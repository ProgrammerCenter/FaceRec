QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 link_pkgconfig

PKGCONFIG += opencv4

LIBS += -lmysqlcppconn
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    facepickframe.cpp \
    facerecframe.cpp \
    main.cpp \
    mainwindow.cpp \
    recognizer.cpp \
    traindialog.cpp \
    trainthread.cpp

HEADERS += \
    database.h \
    facepickframe.h \
    facerecframe.h \
    mainwindow.h \
    recognizer.h \
    traindialog.h \
    trainthread.h

FORMS += \
    facepickframe.ui \
    facerecframe.ui \
    mainwindow.ui \
    traindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    db.ini
