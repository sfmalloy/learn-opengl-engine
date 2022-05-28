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

    glVertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(POSITION_ATTRIB_INDEX);

    glVertexAttribPointer(COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), reinterpret_cast<void*>(3 * sizeof(f32)));
    glEnableVertexAttribArray(COLOR_ATTRIB_INDEX);
}

Mesh::~Mesh() {

}

void Mesh::draw() {
    m_shaderProgram->use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
