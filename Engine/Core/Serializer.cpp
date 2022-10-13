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
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Core/Serializer.h>

namespace DT
{
    void Serialize(Serializer &serializer, std::string &object)
    {
        if (serializer.GetMode() == SerializeMode::S)
            serializer.GetData()[serializer.GetId()++] = object;
        else
            object = serializer.GetData()[serializer.GetId()++];
    }

    void Serialize(Serializer &serializer, float &object)
    {
        if (serializer.GetMode() == SerializeMode::S)
            serializer.GetData()[serializer.GetId()++] = object;
        else
            object = serializer.GetData()[serializer.GetId()++];
    }

    void Serialize(Serializer &serializer, int &object)
    {
        if (serializer.GetMode() == SerializeMode::S)
            serializer.GetData()[serializer.GetId()++] = object;
        else
            object = serializer.GetData()[serializer.GetId()++];
    }

    void Serialize(Serializer &serializer, unsigned int &object)
    {
        if (serializer.GetMode() == SerializeMode::S)
            serializer.GetData()[serializer.GetId()++] = object;
        else
            object = serializer.GetData()[serializer.GetId()++];
    }

    void Serialize(Serializer &serializer, bool &object)
    {
        if (serializer.GetMode() == SerializeMode::S)
            serializer.GetData()[serializer.GetId()++] = object;
        else
            object = serializer.GetData()[serializer.GetId()++];
    }

    void Serialize(Serializer &serializer, glm::vec3 &object)
    {
        serializer & object.x & object.y & object.z;
    }

    void Serialize(Serializer &serializer, glm::vec2 &object)
    {
        serializer & object.x & object.y;
    }

    void Serialize(Serializer &serializer, Mesh &object)
    {
        serializer & object.vertices & object.indices & object.textures;
    }

    void Serialize(Serializer &serializer, Material &object)
    {
        serializer & object.shininess & object.color;
    }

    void Serialize(Serializer &serializer, glm::quat &object)
    {
        serializer & object.x & object.y & object.z & object.w;
    }

    void Serialize(Serializer &serializer, Vertex &object)
    {
        serializer & object.position & object.normal & object.texCoords & object.tangent & object.bitangent;
    }

    void Serialize(Serializer &serializer, Texture &object)
    {
        serializer & object.type & object.path;
    }
}
