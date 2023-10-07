#pragma once

#include <glad/glad.h>
#include <vector>

class BaseMesh
{
public:
    GLuint VAO;
    void createVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices);

private:
    GLuint VBO, EBO;
};