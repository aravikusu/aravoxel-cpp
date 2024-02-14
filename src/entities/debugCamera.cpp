#include "debugCamera.hpp"

void DebugCamera::keyboardInput(GLFWwindow *window, const float deltaTime) {
    const float velocity = movementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
}

void DebugCamera::mouseInput(double xoffset, double yoffset, const GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

glm::mat4 DebugCamera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void DebugCamera::updateCameraVectors() {
    // First the front vector
    glm::vec3 newFront;
    newFront.x = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    newFront.y = static_cast<float>(sin(glm::radians(pitch)));
    newFront.z = static_cast<float>(-cos(glm::radians(yaw)) * cos(glm::radians(pitch)));

    front = glm::normalize(newFront);

    // Then the right/up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

DebugCamera::DebugCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : zoom(ZOOM), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
    this->position = position;
    worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

DebugCamera::DebugCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : zoom(ZOOM), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
    this->position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}
