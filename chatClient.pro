QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += $$QMAKE_LIBS_GUI

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    privatedialog.cpp

HEADERS += \
    client.h \
    logindialog.h \
    mainwindow.h \
    message.h \
    privatedialog.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    privatedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
