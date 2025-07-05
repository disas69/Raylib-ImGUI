#pragma once

#include "rlImGui.h"

#include <functional>

class EditorView
{
public:
    void DrawMenuBar();
    void DrawMainWindow(const RenderTexture* rt, Model* model);

    bool ShouldShutdown() const { return m_shouldShutdown; }

    std::function<void(const char*)> FileOpened;

private:
    const char* m_assetFilters[4] = {"*.obj", "*.glb", "*.gltf", "*.dae"};
    bool m_shouldShutdown = false;
};
