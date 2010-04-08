# -------------------------------------------------
# Project created by QtCreator 2010-03-26T13:44:52
# -------------------------------------------------
QT += network \
    sql \
    xml \
    webkit
TARGET = tippeliga
TEMPLATE = app
SOURCES += main.cpp \
    tippeligaen.cpp \
    player.cpp \
    team.cpp \
    shirt.cpp \
    field.cpp
HEADERS += tippeligaen.h \
    database.h \
    player.h \
    team.h \
    shirt.h \
    field.h
FORMS += tippeligaen.ui
RESOURCES += bilder.qrc
