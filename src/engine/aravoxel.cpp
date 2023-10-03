#include "aravoxel.hpp"

bool Aravoxel::init()
{
    // Initialize SDL, create an OpenGL window...
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << engine::console::error() << "Aravoxel::init: SDL_Init failure:" << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Aravoxel",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1920, 1080,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cout << engine::console::error() << "Aravoxel::init: SDL_CreateWindow failure:" << SDL_GetError() << "\n";
        return false;
    }

    // Set OpenGL attributes.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Need that OpenGL context...
    glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr)
    {
        std::cout << engine::console::error() << "Aravoxel::init: SDL_GL_CreateContext failure:" << SDL_GetError() << "\n";
    }

    // Initalize GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
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
    
    fpsTimer.start();
    drawTest();
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
    while (running)
    {
        render();
        input();

        update();

        SDL_GL_SwapWindow(window);
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
    float averageFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    std::string title = "aravoxel (" + std::to_string((int)averageFPS) + "FPS)";
    SDL_SetWindowTitle(window, title.c_str());
}

void Aravoxel::input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            running = false;

        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
            }
        }
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
        running = true;

        loop();
    }
}

Aravoxel::~Aravoxel()
{
    std::cout << engine::console::aravoxel() << "is terminating.\n";
    resourceManager.clear();
    SDL_DestroyWindow(window);
    SDL_Quit();
}