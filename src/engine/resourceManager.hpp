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

    /// @brief Creates a shader program and stores it for later use.
    /// @param vertexFile/fragmentFile File name + extension.
    /// @param name The name that will be stored so you can retrieve it later.
    static Shader loadShader(const char *vertexFile, const char *fragmentFile, std::string name);
    
    /// @brief Retrieves a created shader program.
    static Shader getShader(std::string name);

    /// @brief Creates a texture and stores it for later user.
    /// @param file File name + extension.
    /// @param alpha Enable transparency or not.
    /// @param name The name that will be stored so you can retrieve it later.
    /// @param flip If the texture should be flipped on the Y axis or not.
    static Texture2D loadTexture(const char *file, bool alpha, std::string name, bool flip = false);
    
    static Texture2D getTexture(std::string name);

    /// @brief Clears all saved shaders and textures.
    static void clear();

private:
    static Shader loadShaderFromFile(const char *vertexFile, const char *fragmentFile);
    static Texture2D loadTextureFromFile(const char *file, bool alpha, bool flip);
};