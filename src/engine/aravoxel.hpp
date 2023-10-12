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

class Aravoxel
{
public:
    Aravoxel();
    ~Aravoxel();

    bool init();
    void loop();
    void update();
    void render();
    void renderDebug();

    void drawTest();

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
    float lastX = engine::SCREEN_WIDTH / 2.0f;
    float lastY = engine::SCREEN_WIDTH / 2.0f;

    DebugCamera camera;

    ResourceManager resourceManager;
    CubeMesh mesh;
    std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

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