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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/mesh.h>
#include <renderer/renderer.h>

namespace DT
{
    Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices) : vertices(_vertices), indices(_indices)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bitangent));
        // ids
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void *)offsetof(Vertex, boneIDs));
        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, weights));
        glBindVertexArray(0);
    }

    Mesh &Mesh::Quad()
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Vertex v0, v1, v2, v3;
        v0.position = glm::vec3(-0.5f, -0.5f, 0.0f);
        v1.position = glm::vec3(0.5f, -0.5f, 0.0f);
        v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
        v3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
        v0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        v0.texCoords = glm::vec2(0.0f, 0.0f);
        v1.texCoords = glm::vec2(1.0f, 0.0f);
        v2.texCoords = glm::vec2(1.0f, 1.0f);
        v3.texCoords = glm::vec2(0.0f, 1.0f);
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        indices = {0, 1, 2, 0, 2, 3};

        static Mesh mesh(vertices, indices);
        return mesh;
    }

    void Mesh::Draw(Renderer &renderer, const glm::mat4 &model, Material &material)
    {
        Shader &shader = material.shader;

        renderer.ActivateShader(shader);
        shader.SetVec3("material.color", material.color);
        shader.SetFloat("material.shininess", material.shininess);
        shader.SetMat4("model", model);

        int textureIndex = 0;
        glActiveTexture(GL_TEXTURE0);

        if (material.diffuseMap.has_value())
        {
            glBindTexture(GL_TEXTURE_2D, material.diffuseMap.value().id);
            shader.SetInt("material.diffuse", textureIndex);
            glActiveTexture(GL_TEXTURE0 + ++textureIndex);
        }

        if (material.specularMap.has_value())
        {
            glBindTexture(GL_TEXTURE_2D, material.specularMap.value().id);
            shader.SetInt("material.specular", textureIndex);
            glActiveTexture(GL_TEXTURE0 + ++textureIndex);
        }

        if (material.normalMap.has_value())
        {
            glBindTexture(GL_TEXTURE_2D, material.normalMap.value().id);
            shader.SetInt("material.normal", textureIndex);
            textureIndex++;
            glActiveTexture(GL_TEXTURE0 + textureIndex);
        }

        if (material.heightMap.has_value())
        {
            glBindTexture(GL_TEXTURE_2D, material.heightMap.value().id);
            shader.SetInt("material.height", textureIndex);
            glActiveTexture(GL_TEXTURE0 + ++textureIndex);
        }

        // if (material.roughnessMap.has_value())
        // {
        //     glBindTexture(GL_TEXTURE_2D, material.roughnessMap.value().id);
        //     shader.SetInt("material.roughness", textureIndex);
        //     glActiveTexture(GL_TEXTURE0 + ++textureIndex);
        // }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
}