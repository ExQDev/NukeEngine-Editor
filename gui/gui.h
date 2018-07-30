#ifndef GUI_H
#define GUI_H
#include <deps/imgui/imgui.h>
#include <deps/imgui/imgui_internal.h>
#include <deps/imgui/imconfig.h>
#include <deps/imgui/stb_rect_pack.h>
#include <config.h>

class GUI
{
private:
    GUI(){}
    ~GUI(){}
public:
    static GUI* getSingleton()
    {
        static GUI instance;
        return &instance;
    }

    void load(char* txt_style)
    {}

    ImVec4 confColor2ImVec(struct confColor cc){
        return ImVec4(cc.x, cc.y, cc.z, cc.w);
    }

    void setup(){
        if(Config::getSingleton()->theme.isLoaded){
            struct NukeTheme *nt = &Config::getSingleton()->theme;
            ImGuiStyle* style = &ImGui::GetStyle();
            style->WindowPadding = ImVec2(nt->WindowPadding.x, nt->WindowPadding.y);
            style->WindowRounding = nt->WindowRounding;
            style->FramePadding = ImVec2(nt->FramePadding.x, nt->FramePadding.y);
            style->FrameRounding = nt->FrameRounding;
            style->ItemSpacing = ImVec2(nt->ItemSpacing.x, nt->ItemSpacing.y);
            style->ItemInnerSpacing = ImVec2(nt->ItemInnerSpacing.x, nt->ItemInnerSpacing.y);
            style->IndentSpacing = nt->IndentSpacing;
            style->ScrollbarSize = nt->ScrollbarSize;
            style->ScrollbarRounding = nt->ScrollbarRounding;
            style->GrabMinSize = nt->GrabMinSize;
            style->GrabRounding = nt->GrabRounding;

            style->Colors[ImGuiCol_Text] = confColor2ImVec(nt->ImGuiCol_Text);
            style->Colors[ImGuiCol_TextDisabled] = confColor2ImVec(nt->ImGuiCol_TextDisabled);
            style->Colors[ImGuiCol_WindowBg] = confColor2ImVec(nt->ImGuiCol_WindowBg);
            style->Colors[ImGuiCol_ChildWindowBg] = confColor2ImVec(nt->ImGuiCol_ChildWindowBg);
            style->Colors[ImGuiCol_PopupBg] = confColor2ImVec(nt->ImGuiCol_PopupBg);
            style->Colors[ImGuiCol_Border] = confColor2ImVec(nt->ImGuiCol_Border);
            style->Colors[ImGuiCol_BorderShadow] = confColor2ImVec(nt->ImGuiCol_BorderShadow);
            style->Colors[ImGuiCol_FrameBg] = confColor2ImVec(nt->ImGuiCol_FrameBg);
            style->Colors[ImGuiCol_FrameBgHovered] = confColor2ImVec(nt->ImGuiCol_FrameBgHovered);
            style->Colors[ImGuiCol_FrameBgActive] = confColor2ImVec(nt->ImGuiCol_FrameBgActive);
            style->Colors[ImGuiCol_TitleBg] = confColor2ImVec(nt->ImGuiCol_TitleBg);
            style->Colors[ImGuiCol_TitleBgCollapsed] = confColor2ImVec(nt->ImGuiCol_TitleBgCollapsed);
            style->Colors[ImGuiCol_TitleBgActive] = confColor2ImVec(nt->ImGuiCol_TitleBgActive);
            style->Colors[ImGuiCol_MenuBarBg] = confColor2ImVec(nt->ImGuiCol_MenuBarBg);
            style->Colors[ImGuiCol_ScrollbarBg] = confColor2ImVec(nt->ImGuiCol_ScrollbarBg);
            style->Colors[ImGuiCol_ScrollbarGrab] = confColor2ImVec(nt->ImGuiCol_ScrollbarGrab);
            style->Colors[ImGuiCol_ScrollbarGrabHovered] = confColor2ImVec(nt->ImGuiCol_ScrollbarGrabHovered);
            style->Colors[ImGuiCol_ScrollbarGrabActive] = confColor2ImVec(nt->ImGuiCol_ScrollbarGrabActive);
            //style->Colors[ImGuiCol_ComboBg] = confColor2ImVec(nt->ImGuiCol_ComboBg);
            style->Colors[ImGuiCol_CheckMark] = confColor2ImVec(nt->ImGuiCol_CheckMark);
            style->Colors[ImGuiCol_SliderGrab] = confColor2ImVec(nt->ImGuiCol_SliderGrab);
            style->Colors[ImGuiCol_SliderGrabActive] = confColor2ImVec(nt->ImGuiCol_SliderGrabActive);
            style->Colors[ImGuiCol_Button] = confColor2ImVec(nt->ImGuiCol_Button);
            style->Colors[ImGuiCol_ButtonHovered] = confColor2ImVec(nt->ImGuiCol_ButtonHovered);
            style->Colors[ImGuiCol_ButtonActive] = confColor2ImVec(nt->ImGuiCol_ButtonActive);
            style->Colors[ImGuiCol_Header] = confColor2ImVec(nt->ImGuiCol_Header);
            style->Colors[ImGuiCol_HeaderHovered] = confColor2ImVec(nt->ImGuiCol_HeaderHovered);
            style->Colors[ImGuiCol_HeaderActive] = confColor2ImVec(nt->ImGuiCol_HeaderActive);
            style->Colors[ImGuiCol_Column] = confColor2ImVec(nt->ImGuiCol_Column);
            style->Colors[ImGuiCol_ColumnHovered] = confColor2ImVec(nt->ImGuiCol_ColumnHovered);
            style->Colors[ImGuiCol_ColumnActive] = confColor2ImVec(nt->ImGuiCol_ColumnActive);
            style->Colors[ImGuiCol_ResizeGrip] = confColor2ImVec(nt->ImGuiCol_ResizeGrip);
            style->Colors[ImGuiCol_ResizeGripHovered] = confColor2ImVec(nt->ImGuiCol_ResizeGripHovered);
            style->Colors[ImGuiCol_ResizeGripActive] = confColor2ImVec(nt->ImGuiCol_ResizeGripActive);
            //style->Colors[ImGuiCol_CloseButton] = confColor2ImVec(nt->ImGuiCol_CloseButton);
            //style->Colors[ImGuiCol_CloseButtonHovered] = confColor2ImVec(nt->ImGuiCol_CloseButtonHovered);
            //style->Colors[ImGuiCol_CloseButtonActive] = confColor2ImVec(nt->ImGuiCol_CloseButtonActive);
            style->Colors[ImGuiCol_PlotLines] = confColor2ImVec(nt->ImGuiCol_PlotLines);
            style->Colors[ImGuiCol_PlotLinesHovered] = confColor2ImVec(nt->ImGuiCol_PlotLinesHovered);
            style->Colors[ImGuiCol_PlotHistogram] = confColor2ImVec(nt->ImGuiCol_PlotHistogram);
            style->Colors[ImGuiCol_PlotHistogramHovered] = confColor2ImVec(nt->ImGuiCol_PlotHistogramHovered);
            style->Colors[ImGuiCol_TextSelectedBg] = confColor2ImVec(nt->ImGuiCol_TextSelectedBg);
            style->Colors[ImGuiCol_ModalWindowDarkening] = confColor2ImVec(nt->ImGuiCol_ModalWindowDarkening);
        }
        else
        {
            setupDefault();
        }
    }

    void setupDefault(){
        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowPadding = ImVec2(15, 15);
        style->WindowRounding = 0.0f;
        style->FramePadding = ImVec2(5, 5);
        style->FrameRounding = 0.0f;
        style->ItemSpacing = ImVec2(6, 6);
        style->ItemInnerSpacing = ImVec2(6, 6);
        style->IndentSpacing = 25.0f;
        style->ScrollbarSize = 15.0f;
        style->ScrollbarRounding = 0.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 3.0f;

        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.80f, 0.48f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.80f, 0.80f, 0.80f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2f, 0.58f, 0.55f, 0.25f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        //style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
        //style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
        //style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
    }
};
#endif // GUI_H
