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

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace DT
{
    /**
     * @brief Shader class for creating and using vertex/fragment shader.
     */
    class Shader
    {
    public:
        unsigned int id;                   ///< @brief Unique id of the shader.
        bool loaded = false;               ///< @brief Boolean variable about whether the shader has been loaded or not.

        /**
         * @brief Create a new Shader object from vertex shader and fragment shader path.
         * @param vertexPath The path to the vertex shader file.
         * @param fragmentPath The path to the fragment shader file.
         */
        Shader(const std::string &vertexPath, const std::string &fragmentPath);

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
        void SetBool(const std::string &name, bool value) const;

        /**
         * @brief set the integer variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable
         */
        void SetInt(const std::string &name, int value) const;

        /**
         * @brief set the float variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable
         */
        void SetFloat(const std::string &name, float value) const;

        /**
         * @brief set the vec2 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec2 type.
         */
        void SetVec2(const std::string &name, const glm::vec2 &value) const;

        /**
         * @brief set the vec2 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec2 variable
         * @param y float value to be assigened to the y component of vec2 variable
         */
        void SetVec2(const std::string &name, float x, float y) const;

        /**
         * @brief set the vec3 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec3 type.
         */
        void SetVec3(const std::string &name, const glm::vec3 &value) const;

        /**
         * @brief set the vec3 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec3 variable.
         * @param y float value to be assigned to the y component of vec3 variable.
         * @param z float value to be assigned to the z component of vec3 variable.
         */
        void SetVec3(const std::string &name, float x, float y, float z) const;

        /**
         * @brief set the vec4 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::vec4 type.
         */
        void SetVec4(const std::string &name, const glm::vec4 &value) const;

        /**
         * @brief set the vec4 variable value in the shader
         * @param name name of the variable
         * @param x float value to be assigned to the x component of vec4 variable.
         * @param y float value to be assigned to the y component of vec4 variable.
         * @param z float value to be assigned to the z component of vec4 variable.
         * @param w float value to be assigned to the w component of vec4 variable.
         */
        void SetVec4(const std::string &name, float x, float y, float z, float w);

        /**
         * @brief set the mat2 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat2 type.
         */
        void SetMat2(const std::string &name, const glm::mat2 &mat) const;

        /**
         * @brief set the mat3 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat3 type.
         */
        void SetMat3(const std::string &name, const glm::mat3 &mat) const;

        /**
         * @brief set the mat4 variable value in the shader
         * @param name name of the variable
         * @param value value to be assigned to the variable. Should be of glm::mat4 type.
         */
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
    };
}