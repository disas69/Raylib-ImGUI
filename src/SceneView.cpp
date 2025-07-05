#include "SceneView.h"
#include "raylib.h"

void SceneView::Setup()
{
    RT = LoadRenderTexture(GetScreenWidth() * 0.825f, GetScreenHeight());

    m_camera.position = { 5.0f, 5.0f, 5.0f };
    m_camera.target = { 0.0f, 0.0f, 0.0f };
    m_camera.up = { 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;

    m_model = LoadModel("resources/dog_001.obj");
    m_texture = LoadTexture("resources/Texture_1.png");
    m_defaultShader = LoadShader(0, 0);
    m_model.materials[0].shader = m_defaultShader;
    m_model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = m_texture;
}

void SceneView::Shutdown()
{
    UnloadRenderTexture(RT);
    UnloadShader(m_defaultShader);
    UnloadTexture(m_texture);
    UnloadModel(m_model);
}

void SceneView::Update()
{
    if (IsWindowResized())
    {
        UnloadRenderTexture(RT);
        RT = LoadRenderTexture(GetScreenWidth() * 0.825f, GetScreenHeight());
    }

    UpdateCamera(&m_camera, CAMERA_ORBITAL);

    BeginTextureMode(RT);
    ClearBackground(RAYWHITE);
    BeginMode3D(m_camera);

    DrawModel(m_model, {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
    DrawGrid(10, 1.0f);

    EndMode3D();
    EndTextureMode();
}

void SceneView::LoadModelAtPath(const char* path)
{
    if (path != nullptr)
    {
        UnloadTexture(m_texture);
        UnloadModel(m_model);

        m_model = LoadModel(path);
        m_texture = LoadTexture("resources/Texture_1.png"); // TODO load actual texture
        m_model.materials[0].shader = m_defaultShader;
        m_model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = m_texture;
    }
}
