#include "voxelWorld.hpp"

void VoxelWorld::init(Settings *settingsRef)
{
    settings = settingsRef;
    Shader shader = resourceManager.loadShader("test.vs", "test.fs", "test");
    resourceManager.loadTexture("container.jpg", false, "container");
    resourceManager.loadTexture("awesomeface.png", true, "awesomeface", true);
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setInteger("texture2", 1);

    mesh.create();
}

void VoxelWorld::render()
{
    Shader shader = resourceManager.getShader("test");
    Texture2D container = resourceManager.getTexture("container");
    Texture2D awesomeface = resourceManager.getTexture("awesomeface");

    container.bind();
    awesomeface.bind(GL_TEXTURE1);

    // Set up model, view, and projection matrix

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)settings->getWidth() / (float)settings->getHeight(), 0.1f, 100.0f);
    shader.setMatrix4("projection", projection);

    glm::mat4 view = camera.getViewMatrix();

    shader.setMatrix4("view", view);

    glBindVertexArray(mesh.VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setMatrix4("model", model, true);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void VoxelWorld::update(GLFWwindow *window, float deltaTime)
{
}

void VoxelWorld::keyInput(GLFWwindow *window, float deltaTime)
{
    camera.keyboardInput(window, deltaTime);
}

void VoxelWorld::mouseInput(double xOffset, double yOffset)
{
    camera.mouseInput(xOffset, yOffset);
}

VoxelWorld::~VoxelWorld()
{
    resourceManager.clear();
}