#-------------------------------------------------
#
# Project created by QtCreator 2021-04-12T15:14:49
#
#-------------------------------------------------

QT += core gui widgets opengl
LIBS += -lm -lGL -lGLU -lglut

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JGT_TEST
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    Objects/torus.cpp \
    initwindow.cpp \
    axes.cpp \
    displaylist.cpp \
    Objects/tile.cpp \
    actions.cpp \
    tableau.cpp \
    Objects/pyramide.cpp \
    Objects/octahedron.cpp \
    Objects/sphere.cpp \
    Objects/cylindre.cpp \
    Objects/decahedron.cpp \
    Monsters/guerrier.cpp \
    Monsters/rogue.cpp \
    Monsters/tank.cpp \
    Monsters/wizard.cpp \
    Objects/cone.cpp \
    Objects/disk.cpp \
    Objects/fleche.cpp

HEADERS += \
    Objects/torus.h \
    library.h \
    initwindow.h \
    axes.h \
    displaylist.h \
    Objects/tile.h \
    actions.h \
    tableau.h \
    Objects/pyramide.h \
    Objects/octahedron.h \
    Objects/sphere.h \
    Objects/cylindre.h \
    Objects/decahedron.h \
    Monsters/guerrier.h \
    Monsters/rogue.h \
    Monsters/tank.h \
    Monsters/wizard.h \
    Objects/cone.h \
    Objects/disk.h \
    Objects/fleche.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
