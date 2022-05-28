#pragma once

#include "types.hpp"
#include "shader.hpp"

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<f32>& data, const std::vector<u32>& indices, ShaderProgram* shaderProgram);
    ~Mesh();
    void draw();
private:
    u32 m_vao;
    u32 m_vbo;
    u32 m_ibo;

    size_t m_size;
    ShaderProgram* m_shaderProgram;
};
