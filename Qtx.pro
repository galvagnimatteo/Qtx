QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Controller/collarcontroller.h \
    Controller/controller.h \
    Controller/maincontroller.h \
    Controller/obliquecontroller.h \
    Controller/rectanglecontroller.h \
    Controller/rectanglewindowcontroller.h \
    Model/c.h \
    Model/collarcut.h \
    Model/deepptr.h \
    Model/mainmodel.h \
    Model/obliquecut.h \
    Model/rawcut.h \
    Model/rectanglecut.h \
    View/collarview.h \
    View/mainwindow.h \
    View/obliqueview.h \
    View/rectangleview.h \
    View/rectanglewindow.h \
    View/view.h

SOURCES += \
    Controller/collarcontroller.cpp \
    Controller/controller.cpp \
    Controller/maincontroller.cpp \
    Controller/obliquecontroller.cpp \
    Controller/rectanglecontroller.cpp \
    Controller/rectanglewindowcontroller.cpp \
    Model/collarcut.cpp \
    Model/mainmodel.cpp \
    Model/obliquecut.cpp \
    Model/rawcut.cpp \
    Model/rectanglecut.cpp \
    View/collarview.cpp \
    View/obliqueview.cpp \
    View/rectangleview.cpp \
    View/rectanglewindow.cpp \
    View/view.cpp \
    main.cpp \
    View/mainwindow.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sources/firefox.png
