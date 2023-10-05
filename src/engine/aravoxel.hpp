#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include "./resourceManager.hpp"
#include "./vertexArrayObject.hpp"
#include "./engine.hpp"

class Aravoxel
{
public:
    Aravoxel();
    ~Aravoxel();

    bool init();
    void loop();
    void update();
    void render();
    void input();

    void drawTest();
private:
    bool running;
    int countedFrames = 0;

    ResourceManager resourceManager;
    VertexArrayObject VAO;


    GLFWwindow* window;
};