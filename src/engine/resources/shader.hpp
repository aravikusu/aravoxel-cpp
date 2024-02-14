#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "../engine.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/// @brief Stores an OpenGL Shader.
/// Has functions for compiling and using a shader program, as well as setting uniforms.
class Shader
{
public:
    GLuint id{};

    Shader() = default;
    Shader &use();

    /// @brief Compile the shaders and create a shader program.
    void compile(const char *vertexSource, const char *fragmentSource);

    // Utilities for changing uniforms
    void setFloat(const char *name, float value, bool useShader = false);
    void setInteger(const char *name, int value, bool useShader = false);
    void setVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
    void setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);

private:
    static void checkCompileErrors(GLuint object, const std::string& type);
};