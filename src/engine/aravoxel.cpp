#include "aravoxel.hpp"

bool Aravoxel::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "aravoxel", NULL, NULL);

    if (window == NULL)
    {
        std::cout << engine::console::error() << "Aravoxel::init: Failed to create GLFW window!" << "\n";
        return false;
    }

    glfwMakeContextCurrent(window);

    // A lambda function in order to get around GLFW not accepting class functions due to being written in C.
    // C limitations...
    auto frameBufferCallback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(window, frameBufferCallback);

    // Initalize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << engine::console::error() << "Aravoxel::init: GLAD could not be initialized!\n";
        return false;
    }

    // Enable some GL functionality we need to wait for GLAD to be initialized for...
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE | GL_BLEND);

    // Initialize shaders
    Shader shader = resourceManager.loadShader("test.vs", "test.fs", "test");
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setInteger("texture2", 1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //fpsTimer.start();
    return true;
}

void Aravoxel::drawTest()
{
    resourceManager.loadTexture("container.jpg", false, "container");
    resourceManager.loadTexture("awesomeface.png", true, "awesomeface", true);
    std::vector<GLfloat> vertices = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    std::vector<GLuint> indices = {
        0, 1, 3,
        1, 2, 3
    };

    VAO.createVAO(vertices, indices);
}

void Aravoxel::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        input();
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
    glClear(GL_COLOR_BUFFER_BIT);

    Shader shader = resourceManager.getShader("test");
    Texture2D container = resourceManager.getTexture("container");
    Texture2D awesomeface = resourceManager.getTexture("awesomeface");
    container.bind();
    awesomeface.bind(GL_TEXTURE1);

    shader.use();
    glBindVertexArray(VAO.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Aravoxel::update()
{
    float averageFPS = countedFrames / glfwGetTime();
    std::string title = "aravoxel (" + std::to_string((int)averageFPS) + "FPS)";
    glfwSetWindowTitle(window, title.c_str());
}

void Aravoxel::input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
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