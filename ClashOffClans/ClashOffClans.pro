QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    castle.cpp \
    defenseunit.cpp \
    empty.cpp \
    fence.cpp \
    level1.cpp \
    levelup.cpp \
    loosing.cpp \
    main.cpp \
    node.cpp \
    objectstruct.cpp \
    start.cpp \
    troobe.cpp

HEADERS += \
    bullet.h \
    castle.h \
    defenseunit.h \
    empty.h \
    fence.h \
    level1.h \
    levelup.h \
    loosing.h \
    node.h \
    objectstruct.h \
    start.h \
    troobe.h

FORMS += \
    levelup.ui \
    loosing.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

DISTFILES += \
    AH.mp3 \
    Background.mp3 \
    Cracking.mp3 \
    LastWin.mp3 \
    Loser.mp3 \
    Win.mp3 \
    shoot.mp3
