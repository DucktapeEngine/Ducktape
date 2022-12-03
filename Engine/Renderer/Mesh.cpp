/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:material
aryanbaburajan2007@gmail.com
*/

#include <Renderer/Mesh.h>

namespace DT
{
    void Mesh::Draw(const glm::mat4 &model, Renderer &renderer)
    {
        // Bind appropriate textures
        for (unsigned int i = 0; i < materials.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            Material *material = materials[i].Data();
            Shader *shader = material->shader.Data();
            renderer.ActivateShader(shader);

            Texture::Type type = material->textureType;

            shader->Use();
            shader->SetVec3("material.diffuseColor", material->diffuseColor);
            shader->SetVec3("material.specularColor", material->specularColor);
            shader->SetVec3("material.ambientColor", material->ambientColor);
            shader->SetFloat("material.shininess", material->shininess);
            shader->SetMat4("model", model);

            shader->SetInt("material.diffuse", i);
            if (type == Texture::Type::DIFFUSE)
                shader->SetInt("material.diffuse", i);
            else if (type == Texture::Type::SPECULAR)
                shader->SetInt("material.specular", i);
            else if (type == Texture::Type::NORMAL)
                shader->SetInt("material.normal", i);
            else if (type == Texture::Type::HEIGHT)
                shader->SetInt("material.height", i);
            glBindTexture(GL_TEXTURE_2D, material->texture.Data()->id);
        }

        // Draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

        // Good practice to set everything back to defaults once configured.
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::Setup()
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
}