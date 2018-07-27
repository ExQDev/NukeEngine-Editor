TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lglut -lGL -lGLEW -pthread -lboost_thread -lboost_system

SOURCES += \
        main.cpp

HEADERS += \
    render/irender.h \
    render/opengl/nukeogl.h \
    input/keyboard.h \
    input/mouse.h
