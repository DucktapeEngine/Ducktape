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

#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <json/json.hpp>
using json = nlohmann::json;

#include <Renderer/Mesh.h>
#include <Renderer/Material.h>
#include <Renderer/Vertex.h>
#include <Renderer/Texture.h>

namespace DT
{
    enum SerializeMode {
        S,
        D
    };

    class Serializer
    {
    protected:
        json data;
        SerializeMode mode;
        int id = 0;

    public:
        Serializer() {}
        Serializer(json existingData) : data(existingData) {}

        inline void SetMode(SerializeMode newMode)
        {
            id = 0;
            mode = newMode;
        }

        inline SerializeMode &GetMode()
        {
            return mode;
        }

        inline void ClearData()
        {
            id = 0;
            data.clear();
        }

        inline void SetData(json &newData)
        {
            data = newData;
        }

        inline json &GetData()
        {
            return data;
        }

        inline void SetId(int &newId)
        {
            id = newId;
        }

        inline int &GetId()
        {
            return id;
        }

        template <typename T>
        Serializer & operator &(T &object)
        {
            Serialize(*this, object);
            return *this;
        }
    };

    template <typename T>
    void Serialize(Serializer &serializer, std::vector<T> &objects)
    {
        for (T object : objects)
            serializer & object;
    }

    void Serialize(Serializer &serializer, std::string &object);
    void Serialize(Serializer &serializer, float &object);
    void Serialize(Serializer &serializer, int &object);
    void Serialize(Serializer &serializer, unsigned int &object);
    void Serialize(Serializer &serializer, bool &object);
    void Serialize(Serializer &serializer, glm::vec3 &object);
    void Serialize(Serializer &serializer, glm::vec2 &object);
    void Serialize(Serializer &serializer, Mesh &object);
    void Serialize(Serializer &serializer, Material &object);
    void Serialize(Serializer &serializer, glm::quat &object);
    void Serialize(Serializer &serializer, Vertex &object);
    void Serialize(Serializer &serializer, Texture &object);
}
