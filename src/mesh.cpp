#include <glad/glad.h>

#include "mesh.hpp"
#include "types.hpp"

Mesh::Mesh(const std::vector<f32>& data, const std::vector<u32>& indices, ShaderProgram* shaderProgram)
    : m_vao(), m_vbo(), m_ibo(), m_size(indices.size()), m_shaderProgram(shaderProgram)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * data.size(), data.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {

}

void Mesh::draw() {
    m_shaderProgram->use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
