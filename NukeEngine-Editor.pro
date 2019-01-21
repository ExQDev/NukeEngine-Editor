TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

ICON += res/logo.ico
win32:RC_ICONS += res/logo.ico

DEFINES += GLM_ENABLE_EXPERIMENTAL EDITOR

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}


SOURCES += \
        main.cpp \

HEADERS += \
    editor/editorui.h \

DISTFILES += \
    res/logo.ico \
    config/main.lua \
    fonts/OpenSansLight.ttf \
    imgui.ini

LIBS += -L/usr/local/lib -lglut -lGL -lGLU -lGLEW -pthread -lboost_thread -lboost_system -lboost_filesystem -llua -ldl -lassimp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/ -lNukeEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/ -lNukeEngine
else:unix: LIBS += -L$$PWD/../NukeEngine/build/$$DESTDIR/ -lNukeEngine

INCLUDEPATH += $$PWD/../NukeEngine \
    $$PWD/../NukeEngine/deps/LuaBridge/Source     # uncomment this if it will tell you that something in LuaBridge cannot be found
DEPENDPATH += $$PWD/../NukeEngine
