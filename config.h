#ifndef CONFIG_H
#define CONFIG_H
#include <backend/lua.h>

struct NukeWindow{
    int w, h;
    std::string mainFont;
    bool hierarchy = true,
            console = true,
            browser = true,
            plugmgr = false,
            about = true,
            inspector = true,
            render = true;
} NukeWindow;

struct confUiVec{
      int x,y;
} confUiVec;


struct confColor{
      float x,y,z,w;
} confColor;


struct NukeTheme{
    bool isLoaded = false;

    struct confUiVec WindowPadding;
    struct confUiVec FramePadding;
    struct confUiVec ItemSpacing;
    struct confUiVec ItemInnerSpacing;
    float WindowRounding;
    float FrameRounding;
    float IndentSpacing;
    float ScrollbarSize;
    float ScrollbarRounding;
    float GrabMinSize;
    float GrabRounding;

    struct confColor ImGuiCol_Text;
    struct confColor ImGuiCol_TextDisabled;
    struct confColor ImGuiCol_WindowBg;
    struct confColor ImGuiCol_ChildWindowBg;
    struct confColor ImGuiCol_PopupBg;
    struct confColor ImGuiCol_Border;
    struct confColor ImGuiCol_BorderShadow;
    struct confColor ImGuiCol_FrameBg;
    struct confColor ImGuiCol_FrameBgHovered;
    struct confColor ImGuiCol_FrameBgActive;
    struct confColor ImGuiCol_TitleBg;
    struct confColor ImGuiCol_TitleBgCollapsed;
    struct confColor ImGuiCol_TitleBgActive;
    struct confColor ImGuiCol_MenuBarBg;
    struct confColor ImGuiCol_ScrollbarBg;
    struct confColor ImGuiCol_ScrollbarGrab;
    struct confColor ImGuiCol_ScrollbarGrabHovered;
    struct confColor ImGuiCol_ScrollbarGrabActive;
    //struct confColor ImGuiCol_ComboBg;
    struct confColor ImGuiCol_CheckMark;
    struct confColor ImGuiCol_SliderGrab;
    struct confColor ImGuiCol_SliderGrabActive;
    struct confColor ImGuiCol_Button;
    struct confColor ImGuiCol_ButtonHovered;
    struct confColor ImGuiCol_ButtonActive;
    struct confColor ImGuiCol_Header;
    struct confColor ImGuiCol_HeaderHovered;
    struct confColor ImGuiCol_HeaderActive;
    struct confColor ImGuiCol_Column;
    struct confColor ImGuiCol_ColumnHovered;
    struct confColor ImGuiCol_ColumnActive;
    struct confColor ImGuiCol_ResizeGrip;
    struct confColor ImGuiCol_ResizeGripHovered;
    struct confColor ImGuiCol_ResizeGripActive;
    //struct confColor ImGuiCol_CloseButton;
    //struct confColor ImGuiCol_CloseButtonHovered;
    //struct confColor ImGuiCol_CloseButtonActive;
    struct confColor ImGuiCol_PlotLines;
    struct confColor ImGuiCol_PlotLinesHovered;
    struct confColor ImGuiCol_PlotHistogram;
    struct confColor ImGuiCol_PlotHistogramHovered;
    struct confColor ImGuiCol_TextSelectedBg;
    struct confColor ImGuiCol_ModalWindowDarkening;
} NukeTheme;

struct confColor luaGetColor(lb::LuaRef ref, const char* name){
    auto col = ref[name];
    struct confColor cc;
    cc.x = ref["r"].cast<float>();
    cc.y = ref["g"].cast<float>();
    cc.z = ref["b"].cast<float>();
    cc.w = ref["a"].cast<float>();
    return cc;
}

struct confUiVec luaGetVector(lb::LuaRef ref, const char* name){
    auto col = ref[name];
    struct confUiVec cc;
    cc.x = ref["x"].cast<int>();
    cc.y = ref["y"].cast<int>();
    return cc;
}

void loadTheme(struct NukeTheme* t, lb::LuaRef _t){
    t->WindowPadding = luaGetVector(_t, "WindowPadding");
    t->FramePadding = luaGetVector(_t, "FramePadding");
    t->ItemSpacing = luaGetVector(_t, "ItemSpacing");
    t->ItemInnerSpacing = luaGetVector(_t, "ItemInnerSpacing");

    t->WindowRounding = _t["WindowRounding"].cast<float>();
    t->FrameRounding = _t["FrameRounding"].cast<float>();
    t->IndentSpacing = _t["IndentSpacing"].cast<float>();
    t->ScrollbarSize = _t["ScrollbarSize"].cast<float>();
    t->ScrollbarRounding = _t["ScrollbarRounding"].cast<float>();
    t->GrabMinSize = _t["GrabMinSize"].cast<float>();
    t->GrabRounding = _t["GrabRounding"].cast<float>();

    t->ImGuiCol_Text = luaGetColor(_t, "ImGuiCol_Text");
    t->ImGuiCol_TextDisabled = luaGetColor(_t, "ImGuiCol_TextDisabled");
    t->ImGuiCol_WindowBg = luaGetColor(_t, "ImGuiCol_WindowBg");
    t->ImGuiCol_ChildWindowBg = luaGetColor(_t, "ImGuiCol_ChildWindowBg");
    t->ImGuiCol_PopupBg = luaGetColor(_t, "ImGuiCol_PopupBg");
    t->ImGuiCol_Border = luaGetColor(_t, "ImGuiCol_Border");
    t->ImGuiCol_BorderShadow = luaGetColor(_t, "ImGuiCol_BorderShadow");
    t->ImGuiCol_FrameBg = luaGetColor(_t, "ImGuiCol_FrameBg");
    t->ImGuiCol_FrameBgHovered = luaGetColor(_t, "ImGuiCol_FrameBgHovered");
    t->ImGuiCol_FrameBgActive = luaGetColor(_t, "ImGuiCol_FrameBgActive");
    t->ImGuiCol_TitleBg = luaGetColor(_t, "ImGuiCol_TitleBg");
    t->ImGuiCol_TitleBgCollapsed = luaGetColor(_t, "ImGuiCol_TitleBgCollapsed");
    t->ImGuiCol_TitleBgActive = luaGetColor(_t, "ImGuiCol_TitleBgActive");
    t->ImGuiCol_MenuBarBg = luaGetColor(_t, "ImGuiCol_MenuBarBg");
    t->ImGuiCol_ScrollbarBg = luaGetColor(_t, "ImGuiCol_ScrollbarBg");
    t->ImGuiCol_ScrollbarGrab = luaGetColor(_t, "ImGuiCol_ScrollbarGrab");
    t->ImGuiCol_ScrollbarGrabHovered = luaGetColor(_t, "ImGuiCol_ScrollbarGrabHovered");
    t->ImGuiCol_ScrollbarGrabActive = luaGetColor(_t, "ImGuiCol_ScrollbarGrabActive");
    //t->ImGuiCol_ComboBg = luaGetColor(_t, "ImGuiCol_ComboBg");
    t->ImGuiCol_CheckMark = luaGetColor(_t, "ImGuiCol_CheckMark");
    t->ImGuiCol_SliderGrab = luaGetColor(_t, "ImGuiCol_SliderGrab");
    t->ImGuiCol_SliderGrabActive = luaGetColor(_t, "ImGuiCol_SliderGrabActive");
    t->ImGuiCol_Button = luaGetColor(_t, "ImGuiCol_Button");
    t->ImGuiCol_ButtonHovered = luaGetColor(_t, "ImGuiCol_ButtonHovered");
    t->ImGuiCol_ButtonActive = luaGetColor(_t, "ImGuiCol_ButtonActive");
    t->ImGuiCol_Header = luaGetColor(_t, "ImGuiCol_Header");
    t->ImGuiCol_HeaderHovered = luaGetColor(_t, "ImGuiCol_HeaderHovered");
    t->ImGuiCol_HeaderActive = luaGetColor(_t, "ImGuiCol_HeaderActive");
    t->ImGuiCol_Column = luaGetColor(_t, "ImGuiCol_Column");
    t->ImGuiCol_ColumnHovered = luaGetColor(_t, "ImGuiCol_ColumnHovered");
    t->ImGuiCol_ColumnActive = luaGetColor(_t, "ImGuiCol_ColumnActive");
    t->ImGuiCol_ResizeGrip = luaGetColor(_t, "ImGuiCol_ResizeGrip");
    t->ImGuiCol_ResizeGripHovered = luaGetColor(_t, "ImGuiCol_ResizeGripHovered");
    t->ImGuiCol_ResizeGripActive = luaGetColor(_t, "ImGuiCol_ResizeGripActive");
    //t->ImGuiCol_CloseButton = luaGetColor(_t, "ImGuiCol_CloseButton");
    //t->ImGuiCol_CloseButtonHovered = luaGetColor(_t, "ImGuiCol_CloseButtonHovered");
    //t->ImGuiCol_CloseButtonActive = luaGetColor(_t, "ImGuiCol_CloseButtonActive");
    t->ImGuiCol_PlotLines = luaGetColor(_t, "ImGuiCol_PlotLines");
    t->ImGuiCol_PlotLinesHovered = luaGetColor(_t, "ImGuiCol_PlotLinesHovered");
    t->ImGuiCol_PlotHistogram = luaGetColor(_t, "ImGuiCol_PlotHistogram");
    t->ImGuiCol_PlotHistogramHovered = luaGetColor(_t, "ImGuiCol_PlotHistogramHovered");
    t->ImGuiCol_TextSelectedBg = luaGetColor(_t, "ImGuiCol_TextSelectedBg");
    t->ImGuiCol_ModalWindowDarkening = luaGetColor(_t, "ImGuiCol_ModalWindowDarkening");

    t->isLoaded = true;
}

class Config
{
private:
    Config() {
        Lua* lua = Lua::getSingleton();
        bfs::path configDir("config");
        bfs::path config("./config/main.lua");
        if(!bfs::exists(configDir))
            bfs::create_directory(configDir);
        if(!bfs::exists(config))
        {
            cout << "Main config not found, create it please!" << endl;
            return;
        }
        boost::filesystem::recursive_directory_iterator iter(configDir), eod;
        for(auto & p : iter)
        {
            cout << "[config] " << p.path().generic_path().c_str() << endl;
            lua->doFile(p.path().c_str());
        }
        auto w = lb::getGlobal(lua->l, "window");
        if(!w.isNil()){
            window.h = w["height"].cast<int>();
            window.w = w["width"].cast<int>();
            window.mainFont = w["mainFont"].cast<std::string>();
        }

        auto t = lb::getGlobal(lua->l, "theme");
        if(!t.isNil()){
            loadTheme(&theme, t);
        }
    }
    ~Config() {}
public:
    struct NukeWindow window {};
    struct NukeTheme theme{};
    static Config* getSingleton(){
        static Config instance;
        return &instance;
    }
};
#endif // CONFIG_H
