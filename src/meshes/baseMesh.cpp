#include "baseMesh.hpp"

void BaseMesh::createVAO(const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Only make a buffer for EBO if we actually have indices.
    if (!indices.empty())
        glGenBuffers(1, &EBO);

    // Bind VAO first, before we touch the VBO and vertex stuff...
    glBindVertexArray(VAO);

    // Bind VBO data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(GLfloat)), vertices.data(),
                 GL_STATIC_DRAW);

    // Again, if we don't have indices we don't make an EBO.
    if (!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(GLfloat)), indices.data(),
                     GL_STATIC_DRAW);
    }
}
