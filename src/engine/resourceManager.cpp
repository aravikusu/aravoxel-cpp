#include "resourceManager.hpp"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::loadShader(const char *vertexFile, const char *fragmentFile, std::string name)
{
    shaders[name] = loadShaderFromFile(vertexFile, fragmentFile);
    return shaders[name];
}

Texture2D ResourceManager::loadTexture(const char *file, bool alpha, std::string name, bool flip)
{
    textures[name] = loadTextureFromFile(file, alpha, flip);
    return textures[name];
}

Shader ResourceManager::getShader(std::string name)
{
    return shaders[name];
}

Texture2D ResourceManager::getTexture(std::string name)
{
    return textures[name];
}

void ResourceManager::clear()
{
    for (auto iter : shaders)
        glDeleteProgram(iter.second.id);
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
    
    std::cout << engine::console::info() << "ResourceManager has been cleared.\n";
}

Shader ResourceManager::loadShaderFromFile(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexShaderFile.open(engine::SHADER_DIR + vertexFile);
        fragmentShaderFile.open(engine::SHADER_DIR + fragmentFile);

        // Read the buffers...
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();

        // Clean up after ourselves...
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Store 'em
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << engine::console::error() << "Failed to read shader files\n";
    }
    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    Shader shader;
    shader.compile(vertexShaderCode, fragmentShaderCode);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char * file, bool alpha, bool flip)
{   
    Texture2D texture;
    if (alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    stbi_set_flip_vertically_on_load(flip);

    std::string filePath = engine::TEXTURE_DIR + file;
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        texture.generate(width, height, data);
        std::cout << engine::console::success() << "Successfully created texture " << file << "!\n";
    }
    else
    {
        std::cout << engine::console::error() << "Failed to load texture " << file << ".\n"; 
    }

    stbi_image_free(data);
    return texture;
}