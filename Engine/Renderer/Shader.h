/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#pragma once

#include <Core/Context.h>

namespace DT
{
    class Shader
    {
    public:
        unsigned int id = 0;

        Shader(unsigned int _id) : id(_id) {}
        Shader(const std::string &frag, const std::string &vert, Error *error);

        Error Use();
        void Delete();


        inline void SetBool(const std::string &name, bool value)
        {
            glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
        }

        inline void SetInt(const std::string &name, int value)
        {
            glUniform1i(glGetUniformLocation(id, name.c_str()), value);
        }

        inline void SetFloat(const std::string &name, float value)
        {
            glUniform1f(glGetUniformLocation(id, name.c_str()), value);
        }

        inline void SetVec2(const std::string &name, const glm::vec2 &value)
        {
            glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }

        inline void SetVec2(const std::string &name, float x, float y)
        {
            glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
        }

        inline void SetVec3(const std::string &name, const glm::vec3 &value)
        {
            glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }

        inline void SetVec3(const std::string &name, float x, float y, float z)
        {
            glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
        }

        inline void SetVec4(const std::string &name, const glm::vec4 &value)
        {
            glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }

        inline void SetVec4(const std::string &name, float x, float y, float z, float w)
        {
            glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
        }

        inline void SetMat2(const std::string &name, const glm::mat2 &mat)
        {
            glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        inline void SetMat3(const std::string &name, const glm::mat3 &mat)
        {
            glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }

        inline void SetMat4(const std::string &name, const glm::mat4 &mat)
        {
            glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
        }
        
        static ErrorOr<Shader> Load(const std::filesystem::path &fragPath, const std::filesystem::path &vertPath);
        static Shader Default(Context &ctx);

        static void CheckCompileErrors(unsigned int shader, const std::string &shaderCode, Error *error);
        static void CheckLinkErrors(unsigned int program, Error *error);
        static void ClearCache(Context &ctx);
    
    private:
        static inline std::unordered_map<std::filesystem::path, Shader> cache;
    };
}