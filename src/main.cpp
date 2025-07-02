#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include <algorithm>

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

		        float toolBarWidth = std::max(260.0f, ImGui::GetContentRegionAvail().x * 0.25f);
		        if (ImGui::BeginChild("Toolbar", ImVec2(toolBarWidth, 0.0f)))
		        {
		            ImGui::Text("Details");
		            ImGui::NewLine();
		            ImGui::Text("Properties");
		        }
		        ImGui::EndChild();

		        ImGui::SameLine();

		        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.9f));
		        if (ImGui::BeginChild("Main View", ImVec2(0.0f, 0.0f), ImGuiChildFlags_None))
		        {
		            float width = ImGui::GetContentRegionAvail().x;
		            float height = ImGui::GetContentRegionAvail().y;
		            ImGui::Image(ImTextureID(image.id), ImVec2(width, height));
		        }
		        ImGui::EndChild();
		        ImGui::PopStyleColor();

		        // ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		        // ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		        // ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Always);
		        // if (ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		        // {
		        //
		        // }
		        // ImGui::End();
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