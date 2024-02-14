#pragma once

#include <glad/glad.h>
#include <iostream>

/// @brief Stores a 2D texture.
/// Has functions for creating as well as using a texture.
class Texture2D {
public:
    Texture2D();

    /// @brief  Create your texture.
    void generate(GLsizei width, GLsizei height, const unsigned char *data);

    /// @brief Binds the texture for use in rendering.
    /// @param activeTextureSlot The active texture slot to be used.
    void bind(GLuint activeTextureSlot = GL_TEXTURE0) const;

    GLuint id{};

    GLuint width, height;

    GLint internalFormat;
    GLuint imageFormat;

    GLint wrapS;
    GLint wrapT;
    GLint filterMin;
    GLint filterMax;
};
