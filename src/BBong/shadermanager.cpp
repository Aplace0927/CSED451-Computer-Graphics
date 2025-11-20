#include "BBong/shadermanager.hpp"

namespace BBong {
    ShaderManager::ShaderManager() {
        removeProgram();
        programID = 0;
    }

    ShaderManager::~ShaderManager() {
        programID = 0;
        uniformLocationCache.clear();
        removeProgram();
    }
 
    void ShaderManager::init() {
        std::vector<ShaderInfo> shaders = {
            {"../src/shader/vert_shader.glsl", GL_VERTEX_SHADER},
            {"../src/shader/frag_shader.glsl", GL_FRAGMENT_SHADER},
        };
        programID = installShaders(shaders);

        if (programID == 0) {
            std::cerr << "[SHADER] Shader program initialization failed!" << std::endl;
        }
    }

    GLint ShaderManager::getUniformLocation(const std::string &symbol) {
        if (uniformLocationCache.find(symbol) != uniformLocationCache.end()) {
            return uniformLocationCache[symbol];
        }
        GLint location = glGetUniformLocation(programID, symbol.c_str());
        if (location == -1) {
            std::cerr << "[SHADER] Uniform Variable '" << symbol << "' Not found in shader program." << std::endl;
        }
        uniformLocationCache[symbol] = location;
        return location;
    }

    GLuint ShaderManager::installShaders(const std::vector<ShaderInfo> &shaderInformations) {
        std::vector<GLuint> shaderIDs;
        GLint success;

        std::cerr << "[SHADER] Installing shaders..." << std::endl;

        GLuint program = glCreateProgram();

        std::cerr << "[SHADER] Created program with ID: " << program << std::endl;
        
        // Compile and attach each shader
        for (const auto &shaderInfo: shaderInformations) {
            GLint shaderID = compileShader(shaderInfo.first, shaderInfo.second);

            if (shaderID == -1) {
                throw std::runtime_error("[SHADER] Failed to compile shader: " + shaderInfo.first);
            }
            shaderIDs.push_back(shaderID);
            glAttachShader(program, shaderID);
        }    

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[LOG_BUFFER_SIZE];
            glGetProgramInfoLog(program, LOG_BUFFER_SIZE, nullptr, infoLog);
            std::cerr << "[SHADER] Program linking failed!\n" << std::string(infoLog) << std::endl;
        }
        else {
            std::cerr << "[SHADER] Program linked successfully. (Program ID: " << program << ")" << std::endl;
        }

        for (const auto &shaderID : shaderIDs) {
            glDeleteShader(shaderID);
        }

        return program;
    }

    GLint ShaderManager::compileShader(const std::string shaderPath, GLenum shaderType) {
        GLint success;
        
        std::ifstream shaderFile(shaderPath);

        if (!shaderFile.is_open()) {
            throw std::runtime_error("[SHADER] Failed to open shader file: " + shaderPath);
        }
        
        // Read shader source code
        std::string shaderCode(
            std::istreambuf_iterator<char>(shaderFile.rdbuf()),
            std::istreambuf_iterator<char>()
        );

        const char* shaderSrc = shaderCode.c_str();
        GLint shaderID = glCreateShader(shaderType);
        
        glShaderSource(shaderID, 1, &shaderSrc, nullptr);
        shaderFile.close();

        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            glDeleteShader(shaderID);

            char infoLog[LOG_BUFFER_SIZE];
            glGetShaderInfoLog(shaderID, LOG_BUFFER_SIZE, nullptr, infoLog);
            std::cerr << "[SHADER] Shader compilation failed!\n" << std::string(infoLog) << std::endl;
            return static_cast<GLint>(-1);
        }
        else {
            std::cerr << "[SHADER] " << shaderPath << " compiled successfully. (Shader ID: " << shaderID << ")" << std::endl;
        }

        return shaderID;
    }

    void ShaderManager::attachProgram() {
        glUseProgram(programID);
    }

    void ShaderManager::detachProgram() {
        glUseProgram(0);
    }

    void ShaderManager::removeProgram() {
        if (programID != 0) {
            glDeleteProgram(programID);
        }
        programID = 0;
        uniformLocationCache.clear();
    }

    template<> void ShaderManager::setUniformValue<int>(const std::string &symbol, const int &value) {
        attachProgram();
        glUniform1i(getUniformLocation(symbol), value);
        detachProgram();
    }

    template<> void ShaderManager::setUniformValue<float>(const std::string &symbol, const float &value) {
        attachProgram();
        glUniform1f(getUniformLocation(symbol), value);
        detachProgram();
    }

    template<> void ShaderManager::setUniformValue<glm::vec3>(const std::string &symbol, const glm::vec3 &value) {
        attachProgram();
        glUniform3fv(getUniformLocation(symbol), 1, glm::value_ptr(value));
        detachProgram();
    }

    template<> void ShaderManager::setUniformValue<glm::vec4>(const std::string &symbol, const glm::vec4 &value) {
        attachProgram();
        glUniform4fv(getUniformLocation(symbol), 1, glm::value_ptr(value));
        detachProgram();
    }

    template<> void ShaderManager::setUniformValue<glm::mat3>(const std::string &symbol, const glm::mat3 &value) {
        attachProgram();
        glUniformMatrix3fv(getUniformLocation(symbol), 1, GL_FALSE, glm::value_ptr(value));
        detachProgram();
    }

    template<> void ShaderManager::setUniformValue<glm::mat4>(const std::string &symbol, const glm::mat4 &value) {
        attachProgram();
        glUniformMatrix4fv(getUniformLocation(symbol), 1, GL_FALSE, glm::value_ptr(value));
        detachProgram();
    }
}