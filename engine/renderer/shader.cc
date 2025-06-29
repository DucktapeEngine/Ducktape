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

#include <core/context.h>
#include <renderer/shader.h>

namespace DT
{
    Shader::Shader(const std::string &frag, const std::string &vert)
    {
        // Compile shaders
        unsigned int vertex, fragment;
        const char *vertCode = vert.c_str();
        const char *fragCode = frag.c_str();

        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertCode, NULL);
        glCompileShader(vertex);
        // CheckCompileErrors(vertex, vert, error);

        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragCode, NULL);
        glCompileShader(fragment);
        // CheckCompileErrors(fragment, frag, error);

        // Link program
        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        // CheckLinkErrors(id, error);

        // Cleanup the shaders as they already have been linked and thus are no longer needed
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        std::cout << "Loaded shader with ID " << id << ".\n";
    }

    void Shader::Use()
    {
        glUseProgram(id);
    }

    void Shader::Delete()
    {
        std::cout << "Deleted shader with ID " << id << ".\n";
        glDeleteProgram(id);
    }

    ErrorOr<Shader> Shader::Load(const std::filesystem::path &fragPath, const std::filesystem::path &vertPath)
    {
        if (cache.find(fragPath) != cache.end())
            return Shader(cache.at(fragPath));

        std::ifstream frag(fragPath);
        std::stringstream fragStream;
        fragStream << frag.rdbuf();
        std::ifstream vert(vertPath);
        std::stringstream vertStream;
        vertStream << vert.rdbuf();

        Shader shader(fragStream.str(), vertStream.str());
        cache.insert({fragPath, shader});
        return shader;
    }

    void Shader::ClearCache(Context &ctx)
    {
        for (std::pair<const std::filesystem::path, Shader> &it : cache)
        {
            it.second.Delete();
        }
        cache.clear();
    }

    Shader Shader::Default(Context &ctx)
    {
        static ErrorOr<Shader> defaultShader = Shader::Load(ctx.projectPath / "engine" / "shaders" / "default.frag", ctx.projectPath / "engine" / "shaders" / "default.vert");
        if (defaultShader.HasError())
            ErrorOr<Shader>("Error loading Default shader: \n" + defaultShader.GetError()).Fatal("Shader::Default()");
        return defaultShader.Fatal("Shader::Default()");
    }

    void Shader::CheckCompileErrors(unsigned int shader, const std::string &shaderCode, Error *error)
    {
        int success;
        char infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            *error = Error("Shadercode failed to compile: \n" + std::string(infoLog) + "\n" + shaderCode + "\n");
        }
    }

    void Shader::CheckLinkErrors(unsigned int program, Error *error)
    {
        int success;
        char infoLog[1024];

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 1024, NULL, infoLog);
            *error = Error("Program failed to link: \n" + std::string(infoLog) + "\n" + std::to_string(program) + "\n");
        }
    }
}