#include "shader.hpp"

Shader &Shader::use()
{
    glUseProgram(this->id);
    return *this;
}

void Shader::compile(const char *vertexSource, const char *fragmentSource)
{
    // Create the shaders first
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Create the shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    checkCompileErrors(this->id, "PROGRAM");

    // Now delete the shaders as they're linked
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::setFloat(const char *name, float value, bool useShader)
{
    if (useShader)
    {
        this->use();
    }
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInteger(const char *name, int value, bool useShader)
{
    if (useShader)
    {
        this->use();
    }
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
    {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << engine::console::error() << "Shader::compile: " << type << " compilation failed!\n" << infoLog << "\n";
        }
        else
        {
            std::cout << engine::console::success() << "Shader::compile: Successfully compiled " << type << " shader!\n";
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << engine::console::error() << "Shader::compile: " << type << " linking failed!\n" << infoLog << "\n";
        }
        else
        {
            std::cout << engine::console::success() << "Shader::compile: Successfully linked Shader Program with ID:" << object << "!\n";
        }
    }
}