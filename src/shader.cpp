#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>

#include "shader.hpp"

ShaderProgram::ShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName)
    : m_program()
{
    u32 vertex;
    compileShader(vertexShaderName, GL_VERTEX_SHADER, vertex);
    
    u32 fragment;
    compileShader(fragmentShaderName, GL_FRAGMENT_SHADER, fragment);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_program, 512, NULL, infoLog);
        std::cerr << "Shader linker error : " << infoLog << '\n';
        exit(-1);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::compileShader(const std::string& filename, GLenum shaderType, u32& shader) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File " << filename << " not found";
        exit(-1);
    }

    std::string line;
    std::string fileSource;
    while (std::getline(file, line)) {
        fileSource += line + '\n';
    }

    const char* source = fileSource.c_str();
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << filename << ": Shader compilation error: " << infoLog << '\n';
        exit(-1);
    }

    file.close();
}

void ShaderProgram::use() {
    glUseProgram(m_program);
}
