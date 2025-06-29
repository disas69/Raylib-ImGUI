#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

int main()
{
	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "3D Viewer");
	SetTargetFPS(60);

	rlImGuiSetup();

	Texture image = LoadTexture("resources/parrots.png");
    bool open = true;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		rlImGuiBegin();
		{
		    if (open)
		    {
		        ImGui::ShowDemoWindow(&open);
		    }

		    if (ImGui::Begin("Test Window", nullptr))
		    {
		        rlImGuiImage(&image);
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