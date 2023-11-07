#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../engine/resourceManager.hpp"
#include "../meshes/cubeMesh.hpp"
#include "../entities/debugCamera.hpp"
#include <vector>
#include "../engine/settings.hpp"

/// @brief A test scene used during the learnopengl.com things.
class VoxelWorld
{
public:
    ~VoxelWorld();

    void init(Settings *settingsRef);
    void update(GLFWwindow *window, float deltaTime);
    void render();
    void keyInput(GLFWwindow *window, float deltaTime);
    void mouseInput(double xOffset, double yOffset);

private:
    ResourceManager resourceManager;
    Settings *settings;

    DebugCamera camera;
    CubeMesh mesh;
};