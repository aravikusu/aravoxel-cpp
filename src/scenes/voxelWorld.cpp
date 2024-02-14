#include "voxelWorld.hpp"

void VoxelWorld::init(Settings *settingsRef) {
    settings = settingsRef;
    Shader shader = ResourceManager::loadShader("test.vert", "test.frag", "test");
    ResourceManager::loadTexture("container.jpg", false, "container");
    ResourceManager::loadTexture("awesomeface.png", true, "awesomeface", true);
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setInteger("texture2", 1);

    mesh.create();
}

void VoxelWorld::render() const {
    Shader shader = ResourceManager::getShader("test");
    const Texture2D container = ResourceManager::getTexture("container");
    const Texture2D awesomeface = ResourceManager::getTexture("awesomeface");

    container.bind();
    awesomeface.bind(GL_TEXTURE1);

    // Set up model, view, and projection matrix

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom),
                                            static_cast<float>(settings->getWidth()) / static_cast<float>(settings->
                                                getHeight()), 0.1f, 100.0f);
    shader.setMatrix4("projection", projection);

    const glm::mat4 view = camera.getViewMatrix();

    shader.setMatrix4("view", view);

    glBindVertexArray(mesh.VAO);
    for (unsigned int i = 0; i < 10; i++) {
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        const float angle = 20.0f * static_cast<float>(i);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.setMatrix4("model", model, true);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void VoxelWorld::update(GLFWwindow *window, float deltaTime) {
}

void VoxelWorld::keyInput(GLFWwindow *window, const float deltaTime) {
    camera.keyboardInput(window, deltaTime);
}

void VoxelWorld::mouseInput(const double xOffset, const double yOffset) {
    camera.mouseInput(xOffset, yOffset);
}

VoxelWorld::~VoxelWorld() {
    ResourceManager::clear();
}
