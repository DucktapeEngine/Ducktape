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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Serialization.h>
#include <Core/ResourceManager.h>
#include <Core/Macro.h>

namespace DT
{
    /**
     * @brief Shader class for creating and using vertex/fragment shader.
     */
    class Shader
    {
    public:
        unsigned int id = 0; ///< @brief Unique id of the shader.
        bool loaded = false; ///< @brief Boolean variable about whether the shader has been loaded or not.

        static inline const std::string versionInclude = "#version 440 core\n";
        static inline const std::string ducktapeInclude = "#ifdef DT_SHADER_FRAG\n"
                                                          "out vec4 FragColor;\n"
                                                          "#endif\n"

                                                          "#ifdef DT_SHADER_VERT\n"
                                                          "#define DT_REGISTER_SHADER() void main() {gl_Position = Vert();}\n"
                                                          "#endif\n"
                                                          "#ifdef DT_SHADER_FRAG\n"
                                                          "#define DT_REGISTER_SHADER() void main() {FragColor = Frag();}\n"
                                                          "#endif\n";
        static inline std::unordered_map<RID, Shader *> factoryData;

        Shader() = default;

        Shader(RID shader);

        /**
         * @brief Destroy the Shader object
         */
        ~Shader();

        /**
         * @brief use the current shader
         */
        void Use();

        /**
         * @brief set the boolean variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable
         */
        void SetBool(std::string name, bool value) const;

        /**
         * @brief set the integer variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable
         */
        void SetInt(std::string name, int value) const;

        /**
         * @brief set the float variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable
         */
        void SetFloat(std::string name, float value) const;

        /**
         * @brief set the vec2 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec2 type.
         */
        void SetVec2(std::string name, const glm::vec2 &value) const;

        /**
         * @brief set the vec2 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec2 variable
         * @param y float value to be assigened to the y component of vec2 variable
         */
        void SetVec2(std::string name, float x, float y) const;

        /**
         * @brief set the vec3 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec3 type.
         */
        void SetVec3(std::string name, const glm::vec3 &value) const;

        /**
         * @brief set the vec3 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec3 variable.
         * @param y float value to be assigned to the y component of vec3 variable.
         * @param z float value to be assigned to the z component of vec3 variable.
         */
        void SetVec3(std::string name, float x, float y, float z) const;

        /**
         * @brief set the vec4 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec4 type.
         */
        void SetVec4(std::string name, const glm::vec4 &value) const;

        /**
         * @brief set the vec4 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec4 variable.
         * @param y float value to be assigned to the y component of vec4 variable.
         * @param z float value to be assigned to the z component of vec4 variable.
         * @param w float value to be assigned to the w component of vec4 variable.
         */
        void SetVec4(std::string name, float x, float y, float z, float w);

        /**
         * @brief set the mat2 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat2 type.
         */
        void SetMat2(std::string name, const glm::mat2 &mat) const;

        /**
         * @brief set the mat3 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat3 type.
         */
        void SetMat3(std::string name, const glm::mat3 &mat) const;

        /**
         * @brief set the mat4 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat4 type.
         */
        void SetMat4(std::string name, const glm::mat4 &mat) const;

        static Shader *LoadResource(RID rid);
        static void UnLoadResource(RID rid);

    protected:
        bool CheckCompileErrors(unsigned int shader, std::string type, const std::filesystem::path &path);
    };
}