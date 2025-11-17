#ifndef SHADERUTILITY_HPP
#define SHADERUTILITY_HPP

#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>

#define LOG_BUFFER_SIZE 2048

typedef struct ShaderInfo {
    std::string shaderPath;
    GLenum shaderType;
} ShaderInfo;

GLuint initializeShader(const std::vector<ShaderInfo> &shaderInformations) {
    std::vector<GLuint> shaderIDs;
    GLuint program = glCreateProgram();
    GLint success;

    // Compile and attach each shader
    for (const auto &shaderInfo: shaderInformations) {
        // Load and compile shader from shaderPath
        // This is a placeholder for actual shader loading logic
        // e.g., read file, compile shader, check for errors, etc.
        std::ifstream shaderFile(shaderInfo.shaderPath);

        if (!shaderFile.is_open()) {
            throw std::runtime_error("Failed to open shader file: " + shaderInfo.shaderPath);
        }
        
        // Read shader source code
        std::string shaderCode(
            std::istreambuf_iterator<char>(shaderFile.rdbuf()),
            std::istreambuf_iterator<char>()
        );

        const char* shaderCodeString = shaderCode.c_str();

        int shaderID = glCreateShader(shaderInfo.shaderType);
        glShaderSource(shaderID, 1, &shaderCodeString, nullptr);
        glCompileShader(shaderID);
    
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[LOG_BUFFER_SIZE];
            glGetShaderInfoLog(shaderID, LOG_BUFFER_SIZE, nullptr, infoLog);
            throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
        }
        shaderFile.close();
        shaderIDs.push_back(shaderID);
        glAttachShader(program, shaderID);
    }
    glUseProgram(program);

    // Link the program
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[LOG_BUFFER_SIZE];
        glGetProgramInfoLog(program, LOG_BUFFER_SIZE, nullptr, infoLog);
        throw std::runtime_error("Program linking failed: " + std::string(infoLog));
    }

    // Clean up shaders as they are no longer needed after linking
    for (const auto &shaderID : shaderIDs) {
        glDeleteShader(shaderID);
    }
    return program;
}


#endif // SHADERUTILITY_HPP