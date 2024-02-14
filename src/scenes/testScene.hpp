#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../engine/resourceManager.hpp"
#include "../meshes/cubeMesh.hpp"
#include "../entities/debugCamera.hpp"
#include <vector>
#include "../engine/settings.hpp"

/// @brief A test scene used during the learnopengl.com things.
class TestScene {
public:
    ~TestScene();

    void init(Settings *settingsRef);

    static void update(GLFWwindow *window, float deltaTime);

    void render() const;

    void keyInput(GLFWwindow *window, float deltaTime);

    void mouseInput(double xOffset, double yOffset);

private:
    ResourceManager resourceManager;
    Settings *settings{};

    DebugCamera camera;
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
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };
};
