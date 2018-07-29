#ifndef EDITORUI_H
#define EDITORUI_H
#include <deps/imgui/imgui.h>
#include <deps/imgui/imgui_internal.h>
#include <GL/freeglut.h>
#include <gui/gui.h>

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

static int g_Time = 0;
static GLuint g_FontTexture = 0;

void ImGui_ImplOpenGL2_RenderDrawData(ImDrawData* draw_data)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(draw_data->DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // We are using the OpenGL fixed pipeline to make the example code simpler to read!
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers, polygon fill.
    GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
    GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
    GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound

    // Setup viewport, orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPps (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayMin is typically (0,0) for single viewport apps.
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(draw_data->DisplayPos.x, draw_data->DisplayPos.x + draw_data->DisplaySize.x, draw_data->DisplayPos.y + draw_data->DisplaySize.y, draw_data->DisplayPos.y, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
    ImVec2 pos = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawVert* vtx_buffer = cmd_list->VtxBuffer.Data;
        const ImDrawIdx* idx_buffer = cmd_list->IdxBuffer.Data;
        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + IM_OFFSETOF(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + IM_OFFSETOF(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + IM_OFFSETOF(ImDrawVert, col)));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                // User callback (registered via ImDrawList::AddCallback)
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                ImVec4 clip_rect = ImVec4(pcmd->ClipRect.x - pos.x, pcmd->ClipRect.y - pos.y, pcmd->ClipRect.z - pos.x, pcmd->ClipRect.w - pos.y);
                if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
                {
                    // Apply scissor/clipping rectangle
                    glScissor((int)clip_rect.x, (int)(fb_height - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));

                    // Bind texture, Draw
                    glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                    glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
                }
            }
            idx_buffer += pcmd->ElemCount;
        }
    }

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glPolygonMode(GL_FRONT, (GLenum)last_polygon_mode[0]); glPolygonMode(GL_BACK, (GLenum)last_polygon_mode[1]);
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

class EditorUI
{
private:
    EditorUI() {}
    ~EditorUI() {}
public:
    static EditorUI* getSingleton(){
        static EditorUI instance;
        return &instance;
    }

    ImGuiContext* context;


    void SetUp(){
        context = ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        g_Time = 0;

        // Glut has 1 function for characters and one for "special keys". We map the characters in the 0..255 range and the keys above.
        io.KeyMap[ImGuiKey_Tab]         = '\t'; // == 9 == CTRL+I
        io.KeyMap[ImGuiKey_LeftArrow]   = 256 + GLUT_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow]  = 256 + GLUT_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow]     = 256 + GLUT_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow]   = 256 + GLUT_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp]      = 256 + GLUT_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown]    = 256 + GLUT_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home]        = 256 + GLUT_KEY_HOME;
        io.KeyMap[ImGuiKey_End]         = 256 + GLUT_KEY_END;
        io.KeyMap[ImGuiKey_Insert]      = 256 + GLUT_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete]      = 127;
        io.KeyMap[ImGuiKey_Backspace]   = 8;  // == CTRL+H
        io.KeyMap[ImGuiKey_Space]       = ' ';
        io.KeyMap[ImGuiKey_Enter]       = 13; // == CTRL+M
        io.KeyMap[ImGuiKey_Escape]      = 27;
        io.KeyMap[ImGuiKey_A]           = 'A';
        io.KeyMap[ImGuiKey_C]           = 'C';
        io.KeyMap[ImGuiKey_V]           = 'V';
        io.KeyMap[ImGuiKey_X]           = 'X';
        io.KeyMap[ImGuiKey_Y]           = 'Y';
        io.KeyMap[ImGuiKey_Z] = 'Z';

        GUI::getSingleton()->setup();
    }

    bool ImGui_ImplOpenGL2_CreateFontsTexture()
    {
        // Build texture atlas
        ImGuiIO& io = ImGui::GetIO();
        unsigned char* pixels;
        int width, height;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

        // Upload texture to graphics system
        GLint last_texture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glGenTextures(1, &g_FontTexture);
        glBindTexture(GL_TEXTURE_2D, g_FontTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        // Store our identifier
        io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

        // Restore state
        glBindTexture(GL_TEXTURE_2D, last_texture);

        return true;
    }

    void ImGui_ImplOpenGL2_DestroyFontsTexture()
    {
        if (g_FontTexture)
        {
            ImGuiIO& io = ImGui::GetIO();
            glDeleteTextures(1, &g_FontTexture);
            io.Fonts->TexID = 0;
            g_FontTexture = 0;
        }
    }

    bool    ImGui_ImplOpenGL2_CreateDeviceObjects()
    {
        return ImGui_ImplOpenGL2_CreateFontsTexture();
    }

    void    ImGui_ImplOpenGL2_DestroyDeviceObjects()
    {
        ImGui_ImplOpenGL2_DestroyFontsTexture();
    }

    void preDraw(){
        ImGuiIO& io = ImGui::GetIO();
        int current_time = glutGet(GLUT_ELAPSED_TIME);
        io.DeltaTime = (current_time - g_Time) / 1000.0f;
        g_Time = current_time;
        if (!g_FontTexture)
            ImGui_ImplOpenGL2_CreateDeviceObjects();
        // Start the frame
        ImGui::NewFrame();
    }

    void postDraw(){
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    void Draw(){
        preDraw();

        ImGui::Begin("WIN");
        ImGui::Text("Hello, world %d", 123);
        if (ImGui::Button("Save"))
        {
            // do stuff
        }
        ImGui::End();

        postDraw();
    }

    void Reshape(int w, int h){
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)w, (float)h);
    }

    void MouseWheel(int button, int dir, int x, int y){
        ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2((float)x, (float)y);
            if (dir > 0)
                io.MouseWheel += 1.0;
            else if (dir < 0)
                io.MouseWheel -= 1.0;
        (void)button; // Unused
    }

    void motion(int x, int y){
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2((float)x, (float)y);
    }

    void mouse(int glut_button, int state, int x, int y)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2((float)x, (float)y);
        int button = -1;
        if (glut_button == GLUT_LEFT_BUTTON) button = 0;
        if (glut_button == GLUT_RIGHT_BUTTON) button = 1;
        if (glut_button == GLUT_MIDDLE_BUTTON) button = 2;
        if (button != -1 && state == GLUT_DOWN)
            io.MouseDown[button] = true;
        if (button != -1 && state == GLUT_UP)
            io.MouseDown[button] = false;
    }


    static void ImGui_ImplFreeGLUT_UpdateKeyboardMods()
    {
        ImGuiIO& io = ImGui::GetIO();
        int mods = glutGetModifiers();
        io.KeyCtrl = (mods & GLUT_ACTIVE_CTRL) != 0;
        io.KeyShift = (mods & GLUT_ACTIVE_SHIFT) != 0;
        io.KeyAlt = (mods & GLUT_ACTIVE_ALT) != 0;
    }

    void keyboard(unsigned char c, int x, int y)
    {
        // Send character to imgui
        //printf("char_down_func %d '%c'\n", c, c);
        ImGuiIO& io = ImGui::GetIO();
        if (c >= 32)
            io.AddInputCharacter(c);

        // Store letters in KeysDown[] array as both uppercase and lowercase + Handle GLUT translating CTRL+A..CTRL+Z as 1..26.
        // This is a hacky mess but GLUT is unable to distinguish e.g. a TAB key from CTRL+I so this is probably the best we can do here.
        if (c >= 1 && c <= 26)
            io.KeysDown[c] = io.KeysDown[c - 1 + 'a'] = io.KeysDown[c - 1 + 'A'] = true;
        else if (c >= 'a' && c <= 'z')
            io.KeysDown[c] = io.KeysDown[c - 'a' + 'A'] = true;
        else if (c >= 'A' && c <= 'Z')
            io.KeysDown[c] = io.KeysDown[c - 'A' + 'a'] = true;
        else
            io.KeysDown[c] = true;
        ImGui_ImplFreeGLUT_UpdateKeyboardMods();
        (void)x; (void)y; // Unused
    }

    void KeyboardUpFunc(unsigned char c, int x, int y)
    {
        //printf("char_up_func %d '%c'\n", c, c);
        ImGuiIO& io = ImGui::GetIO();
        if (c >= 1 && c <= 26)
            io.KeysDown[c] = io.KeysDown[c - 1 + 'a'] = io.KeysDown[c - 1 + 'A'] = false;
        else if (c >= 'a' && c <= 'z')
            io.KeysDown[c] = io.KeysDown[c - 'a' + 'A'] = false;
        else if (c >= 'A' && c <= 'Z')
            io.KeysDown[c] = io.KeysDown[c - 'A' + 'a'] = false;
        else
            io.KeysDown[c] = false;
        ImGui_ImplFreeGLUT_UpdateKeyboardMods();
        (void)x; (void)y; // Unused
    }

    void SpecialFunc(int key, int x, int y)
    {
        //printf("key_down_func %d\n", key);
        ImGuiIO& io = ImGui::GetIO();
        if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
            io.KeysDown[key + 256] = true;
        ImGui_ImplFreeGLUT_UpdateKeyboardMods();
        (void)x; (void)y; // Unused
    }

    void SpecialUpFunc(int key, int x, int y)
    {
        //printf("key_up_func %d\n", key);
        ImGuiIO& io = ImGui::GetIO();
        if (key + 256 < IM_ARRAYSIZE(io.KeysDown))
            io.KeysDown[key + 256] = false;
        ImGui_ImplFreeGLUT_UpdateKeyboardMods();
        (void)x; (void)y; // Unused
    }


};

void editorinit(){
    EditorUI::getSingleton()->SetUp();
}
void editorkeyboard(unsigned char c, int x, int y){
    EditorUI::getSingleton()->keyboard(c,x,y);
}
void editorkeyaboardUp(unsigned char c, int x, int y){
    EditorUI::getSingleton()->KeyboardUpFunc(c,x,y);
}
void editorspecial(int key, int x, int y){
    EditorUI::getSingleton()->SpecialFunc(key, x, y);
}
void editorspecialUp(int key, int x, int y){
    EditorUI::getSingleton()->SpecialUpFunc(key, x, y);
}
void editormouse(int button, int state, int x, int y){
    EditorUI::getSingleton()->mouse(button, state, x, y);
}
void editormove(int x, int y){
    EditorUI::getSingleton()->motion(x, y);
}
void editorpmove(int x, int y){
    EditorUI::getSingleton()->motion(x, y);
}
void editorreshape(int w, int h){
    EditorUI::getSingleton()->Reshape(w, h);
}

void editorDraw(){
    EditorUI::getSingleton()->Draw();
}
#endif // EDITORUI_H
