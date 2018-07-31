TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += GLM_ENABLE_EXPERIMENTAL EDITOR

LIBS += -L/usr/local/lib -lglut -lGL -lGLEW -pthread -lboost_thread -lboost_system -lboost_filesystem -llua -ldl

INCLUDEPATH += deps/imgui

SOURCES += \
        main.cpp \
    deps/imgui/imgui.cpp \
    deps/imgui/imgui_demo.cpp \
    deps/imgui/imgui_draw.cpp \
    API/Model/Vector.cpp

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
    config.h \
    API/Model/Camera.h \
    API/Model/Clock.h \
    API/Model/Collider.h \
    API/Model/Color.h \
    API/Model/Component.h \
    API/Model/Game.h \
    API/Model/GameObject.h \
    API/Model/ID.h \
    API/Model/Include.h \
    API/Model/Layers.h \
    API/Model/Light.h \
    API/Model/Material.h \
    API/Model/Math.h \
    API/Model/Mesh.h \
    API/Model/MeshRenderer.h \
    API/Model/Module.h \
    API/Model/Package.h \
    API/Model/Resource.h \
    API/Model/Scene.h \
    API/Model/Script.h \
    API/Model/Shader.h \
    API/Model/Texture.h \
    API/Model/Time.h \
    API/Model/Transform.h \
    API/Model/Vector.h \
    interface/EditorMenu/MenuItem.h \
    interface/EditorMenu/MenuStrip.h \
    interface/EditorInstance.h \
    interface/NUKEEInteface.h \
    interface/Modular.h \
    interface/AppInstance.h

