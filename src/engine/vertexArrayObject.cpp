#include "vertexArrayObject.hpp"

void VertexArrayObject::createVAO(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Only make a buffer for EBO if we actually have indices.
    if (indices.size() > 0)
        glGenBuffers(1, &EBO);

    // Bind VAO first, before we touch the VBO and vertex stuff...
    glBindVertexArray(VAO);

    // Bind VBO data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Again, if we don't have indices we don't make an EBO.
    if (indices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
    }

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}