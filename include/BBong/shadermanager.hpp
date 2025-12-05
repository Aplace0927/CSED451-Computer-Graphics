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

struct ShaderStateDrawingMethod {
    std::vector<std::pair<GLenum, bool>> capabilitiesStates;
    GLenum polygonMode[2];
    GLfloat polygonOffset[2];
    GLboolean colorMask[4];
    GLboolean depthMask;
    GLfloat lineWidth;
};

class ShaderManager : public Singleton<ShaderManager> {
public:
    ShaderManager();
    ~ShaderManager();

    GLuint addShader(std::string alias, std::string vertexShader, std::string fragmentShader);
    
    GLint getUniformLocation(std::string alias, const std::string &symbol);
    template<typename T> void setUniformValue(std::string alias, const std::string &symbol, const T &value);

    void attachProgram(std::string alias);
    void detachProgram();
    void removeProgram();

    ShaderStateDrawingMethod getCurrentDrawingState();
    void setCurrentDrawingState(const ShaderStateDrawingMethod &state);

private:
    GLuint programID;
    std::vector<GLuint> programs;
    std::map<std::string, GLuint> programAlias;
    std::map<GLuint, std::map<std::string, GLint>> uniformLocationCache;

    GLuint installShaders(const std::vector<ShaderInfo> &shaderInformations);
    GLint compileShader(const std::string shaderPath, GLenum shaderType);
};
}

#endif // SHADERUTILITY_HPP