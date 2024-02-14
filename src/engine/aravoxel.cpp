#include "aravoxel.hpp"

bool Aravoxel::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(settings.getWidth(), settings.getHeight(), "aravoxel", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << engine::console::error() << "Failed to create GLFW window!"
                << "\n";
        return false;
    }

    // We set this pointer to later use it in our callbacks.
    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);
    // glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initalize GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << engine::console::error() << "GLAD could not be initialized!\n";
        return false;
    }

    // Enable some GL functionality we need to wait for GLAD to be initialized for...
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);

    return true;
}

void Aravoxel::loop() {
    while (!glfwWindowShouldClose(window)) {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        keyInput();
        render();
        update();

        glfwPollEvents();
        glfwSwapBuffers(window);

        ++countedFrames;
    }
}

void Aravoxel::keyInput() {
    switch (gameState) {
        case engine::enums::GameState::VOXEL_WORLD:
            voxelWorld.keyInput(window, deltaTime);
            break;
        default: break;
    }
}

void Aravoxel::render() const {
    glClearColor(0.1f, 0.16f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (gameState) {
        case engine::enums::GameState::VOXEL_WORLD:
            voxelWorld.render();
            break;
        default: break;
    }
}

void Aravoxel::update() const {
    const int averageFPS = static_cast<int>(countedFrames / glfwGetTime());
    const std::string title = "aravoxel (" + std::to_string((int) averageFPS) + "FPS)";
    glfwSetWindowTitle(window, title.c_str());
}

void Aravoxel::changeGameState(const engine::enums::GameState state) {
    gameState = state;

    switch (gameState) {
        case engine::enums::VOXEL_WORLD:
            voxelWorld.init(&settings);
            break;
        default: break;
    }
}

Aravoxel::Aravoxel() {
    if (!init()) {
        std::cout <<
                "\033[0;31mInitialization failure!\033[0;37m \n\nCheck the console for further errors that lead here.\n";
    } else {
        std::cout << engine::console::aravoxel() << "is ready for take-off.\n";
        changeGameState(engine::enums::VOXEL_WORLD);
        loop();
    }
}

Aravoxel::~Aravoxel() {
    std::cout << engine::console::aravoxel() << "is terminating.\n";
    glfwTerminate();
}

// Window callbacks below
auto Aravoxel::frameBufferSize(const int width, const int height) -> void {
    glViewport(0, 0, width, height);
}

auto Aravoxel::glfwKey(const int key, int scancode, const int action, [[maybe_unused]] int mods) -> void {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        debug = !debug;

        if (debug) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

auto Aravoxel::glfwMouse(const double xposIn, const double yposIn) -> void {
    const auto xpos = static_cast<float>(xposIn);
    const auto ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    const float xoffset = xpos - lastX;
    const float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    switch (gameState) {
        case engine::enums::GameState::VOXEL_WORLD:
            voxelWorld.mouseInput(xoffset, yoffset);
            break;
        default:
            break;
    }
}
