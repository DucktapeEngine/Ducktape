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

#include <Renderer/Shader.h>

namespace DT
{
    Shader::Shader(RID shaderRID)
    {
        std::filesystem::path shaderPath = ResourceManager::GetPath(shaderRID);

        // Load the vertex/fragment source code from filePath
        std::string fShader;
        std::string vShader;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(shaderPath);
            std::stringstream shaderStream;

            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            fShader = shaderStream.str();
            vShader = shaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << shaderPath << std::endl
                      << e.what() << std::endl;
        }

        vShader = versionInclude + "#define DT_SHADER_VERT\n" + ducktapeInclude + vShader;
        fShader = versionInclude + "#define DT_SHADER_FRAG\n" + ducktapeInclude + fShader;
        const char *vShaderCode = vShader.c_str();
        const char *fShaderCode = fShader.c_str();

        // Compile shaders
        unsigned int vertex, fragment;

        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        if (!CheckCompileErrors(vertex, "VERTEX", shaderPath))
            std::cout << vShaderCode << std::endl;

        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if (!CheckCompileErrors(fragment, "FRAGMENT", shaderPath))
            std::cout << fShaderCode << std::endl;

        // Link program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        CheckCompileErrors(id, "PROGRAM", shaderPath);

        // Cleanup the shaders as they already have been linked and thus are no longer needed
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        loaded = true;
    }

    Shader::~Shader()
    {
        if (deleteOnDestructor)
            glDeleteProgram(id);
    }

    void Shader::Use()
    {
        GLint valid = GL_FALSE;
        glValidateProgram(id);
        glGetProgramiv(id, GL_VALIDATE_STATUS, &valid);
        assert(valid == GL_TRUE);
        glUseProgram(id);
    }

    void Shader::SetBool(std::string name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void Shader::SetInt(std::string name, int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void Shader::SetFloat(std::string name, float value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    bool Shader::CheckCompileErrors(unsigned int shader, std::string type, const std::filesystem::path &path)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << path.string() << "\ntype: " << type << "\n"
                          << infoLog << std::endl;
                return false;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << path.string() << "\ntype: " << type << "\n"
                          << infoLog << std::endl;
                return false;
            }
        }
    }

    void Shader::SetVec2(std::string name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec2(std::string name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
    }

    void Shader::SetVec3(std::string name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec3(std::string name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
    }

    void Shader::SetVec4(std::string name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec4(std::string name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
    }

    void Shader::SetMat2(std::string name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(std::string name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(std::string name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    Shader *Shader::LoadResource(RID rid)
    {
        if (factoryData.count(rid))
            return &factoryData[rid];

        Shader shader(rid);
        factoryData[rid] = shader;
        shader.deleteOnDestructor = false;

        return &factoryData[rid];
    }

    void Shader::UnLoadResource(RID rid)
    {
        factoryData.erase(rid);
    }
}