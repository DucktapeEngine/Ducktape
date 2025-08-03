/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "renderer/mesh.h"
#include "renderer/renderer.h"

namespace dt {
mesh_t::mesh_t(std::vector<vertex> _vertices, std::vector<unsigned int> _indices) : vertices(_vertices), indices(_indices) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, tex_coords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(vertex), (void *)offsetof(vertex, bone_i_ds));
    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, weights));
    glBindVertexArray(0);
}

mesh_t &mesh_t::quad() {
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    vertex v0, v1, v2, v3;

    v0.position = glm::vec3(-0.5f, -0.5f, 0.0f);
    v1.position = glm::vec3(0.5f, -0.5f, 0.0f);
    v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
    v3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
    v0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v0.tex_coords = glm::vec2(0.0f, 0.0f);
    v1.tex_coords = glm::vec2(1.0f, 0.0f);
    v2.tex_coords = glm::vec2(1.0f, 1.0f);
    v3.tex_coords = glm::vec2(0.0f, 1.0f);
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    indices = {0, 1, 2, 0, 2, 3};

    static mesh_t mesh(vertices, indices);
    return mesh;
}
} // namespace dt