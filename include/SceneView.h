#pragma once

#include "raylib.h"

class SceneView
{
public:
    RenderTexture RT;

    void Setup();
    void Shutdown();
    void Update();
    void LoadModelAtPath(const char* path);

    Model* GetModel() { return &m_model; }

private:
    Camera3D m_camera = {0};
    Model m_model = {0};
    Texture2D m_texture = {0};
    Shader m_defaultShader = {0};
};
