#include "shader.hpp"

Shader &Shader::use() {
    glUseProgram(this->id);
    return *this;
}

void Shader::compile(const char *vertexSource, const char *fragmentSource) {
    // Create the shaders first
    const GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    const GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    glShaderSource(fragment, 1, &fragmentSource, nullptr);
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

void Shader::setFloat(const char *name, const float value, const bool useShader) {
    if (useShader) {
        this->use();
    }
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInteger(const char *name, const int value, const bool useShader) {
    if (useShader) {
        this->use();
    }
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVector4f(const char *name, const float x, const float y, const float z, const float w,
                         const bool useShader) {
    if (useShader) {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix, const bool useShader) {
    if (useShader) {
        this->use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(const GLuint object, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cout << engine::console::error() << type << " compilation failed!\n" << infoLog << "\n";
        } else {
            std::cout << engine::console::success() << "Successfully compiled " << type << " shader!\n";
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cout << engine::console::error() << type << " linking failed!\n" << infoLog << "\n";
        } else {
            std::cout << engine::console::success() << "Successfully linked Shader Program with ID:" << object << "!\n";
        }
    }
}
