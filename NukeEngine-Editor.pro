TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lglut -lGL -lGLEW -pthread -lboost_thread -lboost_system -lboost_filesystem -llua

INCLUDEPATH += deps/imgui

SOURCES += \
        main.cpp \
    deps/imgui/imgui.cpp \
    deps/imgui/imgui_demo.cpp \
    deps/imgui/imgui_draw.cpp

HEADERS += \
    backend/lua.h \
    deps/imgui/imconfig.h \
    deps/imgui/imgui.h \
    deps/imgui/imgui_internal.h \
    deps/imgui/stb_rect_pack.h \
    deps/imgui/stb_textedit.h \
    deps/imgui/stb_truetype.h \
    deps/LuaBridge/Source/LuaBridge/detail/CFunctions.h \
    deps/LuaBridge/Source/LuaBridge/detail/ClassInfo.h \
    deps/LuaBridge/Source/LuaBridge/detail/Constructor.h \
    deps/LuaBridge/Source/LuaBridge/detail/dump.h \
    deps/LuaBridge/Source/LuaBridge/detail/FuncTraits.h \
    deps/LuaBridge/Source/LuaBridge/detail/Iterator.h \
    deps/LuaBridge/Source/LuaBridge/detail/LuaException.h \
    deps/LuaBridge/Source/LuaBridge/detail/LuaHelpers.h \
    deps/LuaBridge/Source/LuaBridge/detail/LuaRef.h \
    deps/LuaBridge/Source/LuaBridge/detail/Namespace.h \
    deps/LuaBridge/Source/LuaBridge/detail/Stack.h \
    deps/LuaBridge/Source/LuaBridge/detail/TypeList.h \
    deps/LuaBridge/Source/LuaBridge/detail/TypeTraits.h \
    deps/LuaBridge/Source/LuaBridge/detail/Userdata.h \
    deps/LuaBridge/Source/LuaBridge/LuaBridge.h \
    deps/LuaBridge/Source/LuaBridge/RefCountedObject.h \
    deps/LuaBridge/Source/LuaBridge/RefCountedPtr.h \
    editor/editorui.h \
    gui/gui.h \
    input/keyboard.h \
    input/mouse.h \
    render/opengl/nukeogl.h \
    render/irender.h \
    config.h

