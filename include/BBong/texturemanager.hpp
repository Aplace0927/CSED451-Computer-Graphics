#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>

#include "BBong/singleton.hpp"
#include "BBong/mesh3d.hpp"

namespace BBong {

struct TextureData {
    int width;
    int height;
    int channel;
    GLuint textureID;
};

class TextureManager: public Singleton<TextureManager> {
public:
    TextureManager() = default;
    ~TextureManager() = default;

    void init();
    unsigned int getTexture(const std::string &path);
private:
    unsigned int load(const std::string &path);
    std::map<std::string, TextureData> loadedTextures;
};
}
#endif // TEXTUREMANAGER_HPP