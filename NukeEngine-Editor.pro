TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lglut -lGL -lGLEW -pthread -lboost_thread -lboost_system -lboost_filesystem -llua

SOURCES += \
        main.cpp

HEADERS += \
    render/irender.h \
    render/opengl/nukeogl.h \
    input/keyboard.h \
    input/mouse.h   \
    deps/imgui/* \
    deps/LuaBridge/Source/LuaBridge/* \
    gui/gui.h \
    backend/lua.h \
    config.h
