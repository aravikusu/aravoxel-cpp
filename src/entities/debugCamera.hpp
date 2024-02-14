#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum CAMERA_MOVEMENT {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default constants
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 12.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class DebugCamera {
public:
    float zoom;

    // Constructor with vectors.
    explicit DebugCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                         float yaw = YAW, float pitch = PITCH);

    // Constructor with normal values
    DebugCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    [[nodiscard]] glm::mat4 getViewMatrix() const;

    void keyboardInput(GLFWwindow *window, float deltaTime);

    void mouseInput(double xoffset, double yoffset, GLboolean constrainPitch = true);

private:
    glm::vec3 position{};
    glm::vec3 front;
    glm::vec3 up{};
    glm::vec3 right{};
    glm::vec3 worldUp{};

    double yaw;
    double pitch;
    float movementSpeed;
    float mouseSensitivity;

    bool firstMouse = true;

    // Calculates the front vector from the camera's angles
    void updateCameraVectors();
};
