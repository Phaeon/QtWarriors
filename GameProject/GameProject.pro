#-------------------------------------------------
#
# Project created by QtCreator 2021-04-15T11:23:36
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameProject
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

CONFIG += c++14

SOURCES += \
        Models/Pawns/invisibility_decorator.cpp \
        Models/Pawns/super_attack_decorator.cpp \
        Models/Pawns/super_defence_decorator.cpp \
        main.cpp \
        Views/view.cpp \
        Controllers/controller.cpp \
        Models/start.cpp \
        Views/viewstart.cpp \
        Models/choose.cpp \
        Views/viewchoose.cpp \
        Views/viewgame.cpp \
        Models/Pawns/pawn.cpp \
        Models/Pawns/monster_rogue_.cpp \
        Models/Pawns/monster_wizard_.cpp \
        Models/Pawns/monster_warrior_.cpp \
        Models/Pawns/monster_tank_.cpp \
        Models/Pawns/powerdecorator.cpp \
        Models/Pawns/heal_decorator.cpp \
        Models/Players/player.cpp \
        Models/Players/player_physical.cpp \
        Models/Players/player_ia.cpp \
        Controllers/game_managment.cpp \
        openglwidget.cpp \
        Models/Game.cpp \
        Models/Objects/tile.cpp \
        Models/Objects/tableau.cpp \
        Models/Objects/torus.cpp \
        Models/Objects/sphere.cpp \
        Models/Objects/pyramide.cpp \
        Models/Objects/octahedron.cpp \
        Models/Objects/guerrier.cpp \
        Models/Objects/decahedron.cpp \
        Models/Objects/cylindre.cpp \
        Models/Objects/tank.cpp

HEADERS += \
        Models/Pawns/invisibility_decorator.h \
        Models/Pawns/super_attack_decorator.h \
        Models/Pawns/super_defence_decorator.h \
        config.h \
        Views/view.hpp \
        Controllers/controller.hpp \
        Models/start.hpp \
        Views/viewstart.hpp \
        Models/choose.hpp \
        Views/viewchoose.hpp \
        Views/viewgame.hpp \
        Models/Pawns/pawn.h \
        Models/Pawns/monster_rogue_.h \
        Models/Pawns/monster_wizard_.h \
        Models/Pawns/monster_warrior_.h \
        Models/Pawns/monster_tank_.h \
        Models/Pawns/powerdecorator.h \
        Models/Pawns/heal_decorator.h \
        Models/Players/player.h \
        Models/Players/player_physical.h \
        Models/Players/player_ia.h \
        Controllers/game_managment.h \
        openglwidget.hpp \
        Models/Game.h \
        Models/Objects/tile.h \
        Models/Objects/tableau.h \
        Models/Objects/torus.h \
        Models/Objects/sphere.h \
        Models/Objects/pyramide.h \
        Models/Objects/octahedron.h \
        Models/Objects/guerrier.h \
        Models/Objects/decahedron.h \
        Models/Objects/cylindre.h \
        library.hpp \
        Models/Objects/tank.h \
    stb_image.h


FORMS += \
        Views/viewstart.ui \
        Views/viewchoose.ui \
        Views/viewgame.ui

LIBS += -lm -lGL -lGLU -lglut

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

