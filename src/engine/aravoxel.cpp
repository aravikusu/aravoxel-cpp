#include "aravoxel.hpp"

bool Aravoxel::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(engine::SCREEN_WIDTH, engine::SCREEN_HEIGHT, "aravoxel", NULL, NULL);

    if (window == NULL)
    {
        std::cout << engine::console::error() << "Failed to create GLFW window!"
                  << "\n";
        return false;
    }

    // We set this pointer to later use it in our callbacks.
    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << engine::console::error() << "GLAD could not be initialized!\n";
        return false;
    }

    // Enable some GL functionality we need to wait for GLAD to be initialized for...
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);

    return true;
}

void Aravoxel::drawTest()
{
    Shader shader = resourceManager.loadShader("test.vs", "test.fs", "test");
    resourceManager.loadTexture("container.jpg", false, "container");
    resourceManager.loadTexture("awesomeface.png", true, "awesomeface", true);
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setInteger("texture2", 1);

    mesh.create();
}

void Aravoxel::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.keyboardInput(window, deltaTime);
        render();
        update();

        glfwPollEvents();
        glfwSwapBuffers(window);

        ++countedFrames;
    }
}

void Aravoxel::render()
{
    glClearColor(0.1f, 0.16f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void Aravoxel::update()
{
    float averageFPS = countedFrames / glfwGetTime();
    std::string title = "aravoxel (" + std::to_string((int)averageFPS) + "FPS)";
    glfwSetWindowTitle(window, title.c_str());
}

Aravoxel::Aravoxel()
{
    if (!init())
    {
        std::cout << "\033[0;31mInitialization failure!\033[0;37m \n\nCheck the console for further errors that lead here.\n";
    }
    else
    {
        std::cout << engine::console::aravoxel() << "is ready for take-off.\n";
        drawTest();
        loop();
    }
}

Aravoxel::~Aravoxel()
{
    std::cout << engine::console::aravoxel() << "is terminating.\n";
    resourceManager.clear();
    glfwTerminate();
}

// Window callbacks below
auto Aravoxel::frameBufferSize(int width, int height) -> void
{
    glViewport(0, 0, width, height);
}

auto Aravoxel::glfwKey(int key, int scancode, int action, int mods) -> void
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        debug = !debug;

        if (debug)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

auto Aravoxel::glfwMouse(double xposIn, double yposIn) -> void
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.mouseInput(xoffset, yoffset);
}