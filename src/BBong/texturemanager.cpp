#include "BBong/texturemanager.hpp"


#include "stb/stb_image.h"

namespace BBong {

void TextureManager::init() {
    stbi_set_flip_vertically_on_load(1);
    loadedTextures.clear();
}

GLuint TextureManager::getTexture(const std::string &path) {
    std::map<std::string, TextureData>::iterator it = loadedTextures.find(path);
    if (it != loadedTextures.end()) {
        return it->second.textureID;
    }
    return load(path);
}

GLuint TextureManager::load(const std::string &path) {
    TextureData textureData;
    
    FILE* textureFile = fopen(path.c_str(), "rb");
    if (!textureFile) { 
        std::cerr << "[TEXTUREMANAGER] Error: Could not open texture file: " << path << std::endl;
        return -1;
    }

    unsigned char* data = stbi_load_from_file(
        textureFile,
        (int*)&textureData.width,
        (int*)&textureData.height,
        (int*)&textureData.channel,
        0
    );
    if (!data) {
        std::cerr << "[TEXTUREMANAGER] Error: Could not load texture data from file: " << path << std::endl;
        fclose(textureFile);
        return -1;
    }
    fclose(textureFile);
        
    glGenTextures(1, &textureData.textureID);
    glBindTexture(GL_TEXTURE_2D, textureData.textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (textureData.channel == 3) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            textureData.width,
            textureData.height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else if (textureData.channel == 4) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            textureData.width,
            textureData.height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "[TEXTUREMANAGER] Error: Unsupported number of channels (" 
                  << textureData.channel << ") in texture: " << path << std::endl;
        free(data);
        return -1;
    }
    // glTexStorage2D(
    //     GL_TEXTURE_2D,      // target
    //     1,                  // levels
    //     GL_RGBA8,           // internalformat
    //     textureData.width,  // width
    //     textureData.height  // height
    // );
    // glTexSubImage2D(
    //     GL_TEXTURE_2D,      // target
    //     0,                  // level
    //     0,                  // xoffset
    //     0,                  // yoffset
    //     textureData.width,  // width
    //     textureData.height, // height
    //     GL_RGBA,            // format
    //     GL_UNSIGNED_BYTE,   // type
    //     data                // pixels
    // );
    
    free(data);

    std::cerr << "[TEXTUREMANAGER] Loaded texture: " << path 
              << " (ID: " << textureData.textureID 
              << ", " << textureData.width << "x" << textureData.height 
              << ", Channels: " << textureData.channel << ")" << std::endl;
    loadedTextures[path] = textureData;
    return textureData.textureID;
}   
}
