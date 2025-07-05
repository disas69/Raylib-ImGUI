#include "EditorView.h"
#include "raylib.h"
#include "imgui.h"
#include "tinyfiledialogs.h"

void EditorView::DrawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
                const char* filePath = tinyfd_openFileDialog("Open 3D Model", "", 4, m_assetFilters, "3D model files", 0);
                if (filePath != nullptr)
                {
                    if (FileOpened != nullptr)
                    {
                        FileOpened(filePath);
                    }
                    else
                    {
                        // Default action if no callback is set
                        TraceLog(LOG_INFO, "File opened: %s", filePath);
                    }
                }
            }

            if (ImGui::MenuItem("Quit"))
            {
                m_shouldShutdown = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void EditorView::DrawMainWindow(const RenderTexture* rt, Model* model)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if (ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus))
    {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, ImGui::GetContentRegionAvail().y));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.9f));
        if (ImGui::BeginChild("Main View", ImVec2(0.0f, 0.0f), ImGuiChildFlags_None))
        {
            rlImGuiImageRenderTextureFit(rt, true);
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.3f, 0.3f, 0.3f, 0.9f));
        if (ImGui::BeginChild("Toolbar", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders))
        {
            ImGui::Text("Details:");

            if (model != nullptr)
            {
                ImGui::Text("Meshes: %d", model->meshCount);
                ImGui::Text("Materials: %d", model->materialCount);

                for (int i = 0; i < model->meshCount; i++)
                {
                    ImGui::PushID(i);
                    ImGui::Text("Vertices: %d", model->meshes[i].vertexCount);
                    ImGui::Text("Triangles: %d", model->meshes[i].triangleCount);
                    ImGui::PopID();
                }
            }
            else
            {
                ImGui::Text("No model loaded.");
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
    ImGui::End();
}