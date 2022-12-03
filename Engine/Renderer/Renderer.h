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

#define MAX_LIGHT_NO 25

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Core/Configuration.h>
#include <Core/Window.h>
#include <Core/Debug.h>
#include <Renderer/Cubemap.h>
#include <Core/Context.h>
#include <Core/Macro.h>
#include <Scene/Scene.h>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace DT
{
	class Renderer
	{
	public:
		unsigned int FBO, RBO, renderTexture;
		unsigned int quadVAO, quadVBO;
		unsigned int skyboxVAO, skyboxVBO;
		Cubemap skyboxCubemap;
		Shader screenShader = Shader(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Screen.glsl"));
		Shader skyboxShader = Shader(ResourceManager::GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Shaders" / "Skybox.glsl"));
		glm::vec2 customViewportSize;

		glm::mat4 *cameraView = nullptr;
		glm::mat4 *cameraProjection = nullptr;
		glm::vec3 *cameraPosition = nullptr;
		glm::quat *cameraRotation = nullptr;
		bool *isOrtho = nullptr;
		float *fov = nullptr;

		std::array<bool, MAX_LIGHT_NO> occupiedDirectionalLights = {false};
		std::array<bool, MAX_LIGHT_NO> occupiedPointLight = {false};

		Renderer(Window &window, Configuration &config);
		void Render(Window &window, Configuration &config, Scene *scene);
		~Renderer();

		void SetViewport(glm::vec2 viewportsize);

		void LoadSkybox(std::array<std::filesystem::path, 6> paths);

		bool GetFreeDirectionalLightSpot(unsigned int *spot);
		void UnoccupyDirectionalLightSpot(unsigned int spot);
		bool GetFreePointLightSpot(unsigned int *spot);
		void UnoccupyPointLightSpot(unsigned int spot);

		void ActivateShader(Shader *shader);

		static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
	};
}