#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "SceneView.h"
#include "EditorView.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "3D Viewer");
    SetTargetFPS(60);

    rlImGuiSetup();
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

    SceneView sceneView;
    sceneView.Setup();

    EditorView editorView;
    editorView.FileOpened = [&sceneView](const char* path)
    {
        sceneView.LoadModelAtPath(path);
    };

    while (!WindowShouldClose() && !editorView.ShouldShutdown())
    {
        sceneView.Update();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        rlImGuiBegin();
        editorView.DrawMenuBar();
        editorView.DrawMainWindow(&sceneView.RT, sceneView.GetModel());
        rlImGuiEnd();

        EndDrawing();
    }

    sceneView.Shutdown();
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}