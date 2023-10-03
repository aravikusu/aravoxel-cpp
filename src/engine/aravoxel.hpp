#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <math.h>
#include <vector>
#include "../util/timer.hpp"
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
    Timer fpsTimer;
    int countedFrames;

    ResourceManager resourceManager;
    VertexArrayObject VAO;


    SDL_Window* window;
    SDL_GLContext glContext;
};