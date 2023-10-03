#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "./resources/shader.hpp"
#include "./engine.hpp"
#include "./resources/texture2d.hpp"
#include "../util/stb_image.h"

/// @brief The ResourceManager stores all currently loaded shaders and provides an easy way load and retrieve them.
class ResourceManager
{
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    static Shader loadShader(const char *vertexFile, const char *fragmentFile, std::string name);
    static Shader getShader(std::string name);
    static Texture2D loadTexture(const char *file, bool alpha, std::string name, bool flip = false);
    static Texture2D getTexture(std::string name);
    static void clear();

private:
    static Shader loadShaderFromFile(const char *vertexFile, const char *fragmentFile);
    static Texture2D loadTextureFromFile(const char *file, bool alpha, bool flip);
};