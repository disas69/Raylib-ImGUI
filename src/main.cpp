#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "tinyfiledialogs.h"

const char* m_AssetFilters[] = {"*.png", "*.jpg", "*.bmp", "*.gif"};

int main()
{
    int screenWidth = 1280;
    int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "3D Viewer");
    SetTargetFPS(60);

    rlImGuiSetup();
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

    Texture image = LoadTexture("resources/parrots.png");
    bool open = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        rlImGuiBegin();
        {
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open"))
                    {
                        const char* filePath = tinyfd_openFileDialog("Open Image", "", 4, m_AssetFilters, "Image files", 0);
                        if (filePath != nullptr)
                        {
                            UnloadTexture(image);
                            image = LoadTexture(filePath);
                        }
                    }

                    if (ImGui::MenuItem("Quit"))
                    {
                        CloseWindow();
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Window"))
                {
                    if (ImGui::MenuItem("Demo"))
                    {
                        open = !open;
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }

            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);

            if (ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus))
            {
                if (open)
                {
                    ImGui::ShowDemoWindow(&open);
                }

                ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, ImGui::GetContentRegionAvail().y));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.9f));
                if (ImGui::BeginChild("Main View", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders))
                {
                    float width = ImGui::GetContentRegionAvail().x;
                    float height = ImGui::GetContentRegionAvail().y;
                    ImGui::Image(ImTextureID(image.id), ImVec2(width, height));
                }
                ImGui::EndChild();
                ImGui::PopStyleColor();

                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.3f, 0.3f, 0.3f, 0.9f));
                if (ImGui::BeginChild("Toolbar", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders))
                {
                    ImGui::Text("Details");
                }
                ImGui::EndChild();
                ImGui::PopStyleColor();
            }
            ImGui::End();
        }
        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    UnloadTexture(image);
    CloseWindow();

    return 0;
}