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
    #ifdef SHADER_DIRECTORY
        std::vector<ShaderInfo> shaders = {
            {SHADER_DIRECTORY "vert_shader.glsl", GL_VERTEX_SHADER},
            {SHADER_DIRECTORY "frag_shader.glsl", GL_FRAGMENT_SHADER},
        };
    #else
        std::vector<ShaderInfo> shaders = {
            {"../shader/vert_shader.glsl", GL_VERTEX_SHADER},
            {"../shader/frag_shader.glsl", GL_FRAGMENT_SHADER},
        };
    #endif
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
            glDetachShader(program, shaderID);
            glDeleteShader(shaderID);
        }
        uniformLocationCache.clear();

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

    ShaderStateDrawingMethod ShaderManager::getCurrentDrawingState() {
        std::vector<GLenum> capabilitiesCheck = {
            GL_BLEND,
            GL_CULL_FACE,
            GL_DEPTH_TEST,
            GL_DITHER,
            GL_POLYGON_OFFSET_FILL,
            GL_POLYGON_OFFSET_LINE,
            GL_SCISSOR_TEST,
            GL_STENCIL_TEST
        };
        std::vector<std::pair<GLenum, bool>> capabilitiesStates;
        for (const auto &cap : capabilitiesCheck) {
            capabilitiesStates.push_back({cap, glIsEnabled(cap)});
        }
        ShaderStateDrawingMethod state;
        state.capabilitiesStates = capabilitiesStates;
        glGetIntegerv(GL_POLYGON_MODE, reinterpret_cast<GLint*>(state.polygonMode));
        glGetBooleanv(GL_COLOR_WRITEMASK, reinterpret_cast<GLboolean*>(state.colorMask));
        glGetBooleanv(GL_DEPTH_WRITEMASK, &state.depthMask);
        glGetFloatv(GL_LINE_WIDTH, &state.lineWidth);
        glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &state.polygonOffset[0]);
        glGetFloatv(GL_POLYGON_OFFSET_UNITS, &state.polygonOffset[1]);
        return state;
    }

    void ShaderManager::setCurrentDrawingState(const ShaderStateDrawingMethod &state) {
        for (const auto &capState : state.capabilitiesStates) {
            if (capState.second) {
                glEnable(capState.first);
            } else {
                glDisable(capState.first);
            }
        }
        glPolygonMode(GL_FRONT_AND_BACK, state.polygonMode[0]);
        glColorMask(state.colorMask[0], state.colorMask[1], state.colorMask[2], state.colorMask[3]);
        glDepthMask(state.depthMask);
        glLineWidth(state.lineWidth);
        glPolygonOffset(state.polygonOffset[0], state.polygonOffset[1]);
    }

    template<> void ShaderManager::setUniformValue<int>(const std::string &symbol, const int &value) {
        glUniform1i(getUniformLocation(symbol), value);
    }

    template<> void ShaderManager::setUniformValue<float>(const std::string &symbol, const float &value) {
        glUniform1f(getUniformLocation(symbol), value);
    }

    template<> void ShaderManager::setUniformValue<glm::vec3>(const std::string &symbol, const glm::vec3 &value) {
        glUniform3fv(getUniformLocation(symbol), 1, glm::value_ptr(value));
    }

    template<> void ShaderManager::setUniformValue<glm::vec4>(const std::string &symbol, const glm::vec4 &value) {
        glUniform4fv(getUniformLocation(symbol), 1, glm::value_ptr(value));
    }

    template<> void ShaderManager::setUniformValue<glm::mat3>(const std::string &symbol, const glm::mat3 &value) {
        glUniformMatrix3fv(getUniformLocation(symbol), 1, GL_FALSE, glm::value_ptr(value));
    }

    template<> void ShaderManager::setUniformValue<glm::mat4>(const std::string &symbol, const glm::mat4 &value) {
        glUniformMatrix4fv(getUniformLocation(symbol), 1, GL_FALSE, glm::value_ptr(value));
    }
}