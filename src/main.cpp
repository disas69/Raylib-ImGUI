#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

int main(int argc, char* argv[])
{
	// Initialization
	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "3D Viewer");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	Texture image = LoadTexture("resources/parrots.png");

	// Main game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// start ImGui Conent
		rlImGuiBegin();

		// show ImGui Content
		bool open = true;
		ImGui::ShowDemoWindow(&open);

		open = true;
		if (ImGui::Begin("Test Window", &open))
		{
			rlImGuiImage(&image);
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();

		EndDrawing();
	}

	// De-Initialization
    rlImGuiShutdown();
	UnloadTexture(image);
	CloseWindow();

	return 0;
}