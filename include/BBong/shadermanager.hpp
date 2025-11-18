#ifndef SHADERUTILITY_HPP
#define SHADERUTILITY_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include "BBong/singleton.hpp"
#include "config.hpp"

#define LOG_BUFFER_SIZE 2048

namespace BBong {

typedef std::pair<std::string, GLenum> ShaderInfo;

class ShaderManager : public Singleton<ShaderManager> {
public:
    ShaderManager();
    ~ShaderManager();

    void init();
    
    GLint getUniformLocation(const std::string &symbol);
    template<typename T> void setUniformValue(const std::string &symbol, const T &value);

    void attachProgram();
    void detachProgram();
    void removeProgram();

private:
    GLuint programID;
    std::map<std::string, GLint> uniformLocationCache;

    GLuint installShaders(const std::vector<ShaderInfo> &shaderInformations);
    GLint compileShader(const std::string shaderPath, GLenum shaderType);
};
}

#endif // SHADERUTILITY_HPP