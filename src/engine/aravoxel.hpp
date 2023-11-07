#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include "./resourceManager.hpp"
#include "./engine.hpp"
#include "../meshes/cubeMesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../entities/debugCamera.hpp>
#include "../scenes/testScene.hpp"
#include "../scenes/voxelWorld.hpp"
#include "./settings.hpp"

class Aravoxel
{
public:
    Aravoxel();
    ~Aravoxel();

    bool init();
    void keyInput();
    void loop();
    void update();
    void render();
    void renderDebug();

    void changeGameState(engine::enums::GameState state);

    // CALLBACKS BELOW \\
    // Has to be this way.
    void frameBufferSize(int width, int height);
    void glfwKey(int key, int scancode, int action, int mods);
    void glfwMouse(double xposIn, double yposIn);

private:
    bool debug;
    int countedFrames = 0;
    float deltaTime;
    float lastFrame;

    bool firstMouse = true;
    float lastX = settings.getHeight() / 2.0f;
    float lastY = settings.getWidth() / 2.0f;

    engine::enums::GameState gameState = engine::enums::GameState::INIT;
    Settings settings;

    TestScene test;
    VoxelWorld voxelWorld;

    GLFWwindow *window;

    // CALLBACKS BELOW \\ 
    // Strange hacking to get around GLFW only wanting to use static non-class functions for callbacks
    // due to it being written in C.
    inline static auto frameBufferSizeCallback(GLFWwindow *window, int width, int height) -> void
    {
        Aravoxel *aravoxel = static_cast<Aravoxel *>(glfwGetWindowUserPointer(window));
        aravoxel->frameBufferSize(width, height);
    }

    inline static auto keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Aravoxel *aravoxel = static_cast<Aravoxel *>(glfwGetWindowUserPointer(window));
        aravoxel->glfwKey(key, scancode, action, mods);
    }
    inline static auto mouseCallback(GLFWwindow *window, double xposIn, double yposIn)
    {
        Aravoxel *aravoxel = static_cast<Aravoxel *>(glfwGetWindowUserPointer(window));
        aravoxel->glfwMouse(xposIn, yposIn);
    }
};