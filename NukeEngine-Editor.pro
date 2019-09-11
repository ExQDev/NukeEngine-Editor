TEMPLATE = app
CONFIG += console c++14
CONFIG += x86_64
CONFIG -= app_bundle
CONFIG -= qt

unix:!macx{
ICON += res/logo.ico
}
win32:RC_ICONS += res/logo.ico
macx{
ICON = myapp.icns
}

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
    imgui.ini \
    res/logo.icns


macx{
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/release/ -lNukeEngine.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/debug/ -lNukeEngine.1.0.0
else:unix: LIBS += -L$$PWD/../NukeEngine/build/debug/ -lNukeEngine.1.0.0

LIBS += -L/System/Library -L/Library -L~/Library -L/usr/local/lib -lboost_thread-mt -lboost_system -lboost_filesystem -llua -lassimp -lGLEW -lGLUT -framework OpenGL -framework GLUT -framework Cocoa -framework CoreFoundation

INCLUDEPATH += $$PWD/../NukeEngine \
    /usr/local/include \
    $$PWD/../NukeEngine/deps/glm \
    $$PWD/../NukeEngine/deps \
    $$PWD/../NukeEngine/deps/LuaBridge/Source

DEPENDPATH += $$PWD/../NukeEngine

DEFINES += __APPLE__

}

!macx{
LIBS += -L/usr/local/lib -lglut -lGL -lGLU -lGLEW -pthread -lboost_thread -lboost_system -lboost_filesystem -llua -ldl -lassimp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/ -lNukeEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../NukeEngine/build/debug/ -lNukeEngine
else:unix: LIBS += -L$$PWD/../NukeEngine/build/$$DESTDIR/ -lNukeEngine

INCLUDEPATH += $$PWD/../NukeEngine \
    $$PWD/../NukeEngine/deps/LuaBridge/Source    # uncomment this if it will tell you that something in LuaBridge cannot be found

DEPENDPATH += $$PWD/../NukeEngine
}
