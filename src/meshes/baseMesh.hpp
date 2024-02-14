#pragma once

#include <glad/glad.h>
#include <vector>

class BaseMesh {
public:
    GLuint VAO{};

    void createVAO(const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices = {});

private:
    GLuint VBO{}, EBO{};
};
