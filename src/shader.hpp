#pragma once

#include <glad/glad.h>

#include <string>

#include "types.hpp"

class ShaderProgram {
public:
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName);
    ~ShaderProgram();

    void use();
private:
    void compileShader(const std::string& filename, GLenum shaderType, u32& shader);

    u32 m_program;
};
