#include "testScene.hpp"

void TestScene::init()
{
    Shader shader = resourceManager.loadShader("test.vs", "test.fs", "test");
    resourceManager.loadTexture("container.jpg", false, "container");
    resourceManager.loadTexture("awesomeface.png", true, "awesomeface", true);
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setInteger("texture2", 1);

    mesh.create();
}

void TestScene::render()
{
    Shader shader = resourceManager.getShader("test");
    Texture2D container = resourceManager.getTexture("container");
    Texture2D awesomeface = resourceManager.getTexture("awesomeface");

    container.bind();
    awesomeface.bind(GL_TEXTURE1);

    // Set up model, view, and projection matrix
    
    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)engine::SCREEN_WIDTH / (float)engine::SCREEN_HEIGHT, 0.1f, 100.0f);
    shader.setMatrix4("projection", projection);

    glm::mat4 view = camera.getViewMatrix();

    shader.setMatrix4("view", view);

    glBindVertexArray(mesh.VAO);
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.setMatrix4("model", model, true);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TestScene::update(GLFWwindow* window, float deltaTime)
{

}

void TestScene::keyInput(GLFWwindow* window, float deltaTime)
{
    camera.keyboardInput(window, deltaTime);
}

void TestScene::mouseInput(double xOffset, double yOffset)
{
    camera.mouseInput(xOffset, yOffset);
}

TestScene::~TestScene()
{
    resourceManager.clear();
}