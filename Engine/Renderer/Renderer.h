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
#include <Core/Window.h>
#include <Core/Debug.h>
#include <Core/Macro.h>
#include <Scene/Scene.h>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace DT
{
	/**
	 * @class Renderer
	 * @brief Handles rendering operations and manages rendering resources.
	 */
	class Renderer
	{
	public:
		unsigned int FBO;													/**< Framebuffer object ID. */
		unsigned int RBO;													/**< Renderbuffer object ID. */
		unsigned int renderTexture;											/**< ID of the texture used for rendering. */
		unsigned int quadVAO;												/**< Vertex Array Object ID for the quad. */
		unsigned int quadVBO;												/**< Vertex Buffer Object ID for the quad. */
		unsigned int skyboxVAO;												/**< Vertex Array Object ID for the skybox. */
		unsigned int skyboxVBO;												/**< Vertex Buffer Object ID for the skybox. */
		glm::mat4 *cameraView = nullptr;									/**< Pointer to the view matrix of the camera. */
		glm::mat4 *cameraProjection = nullptr;								/**< Pointer to the projection matrix of the camera. */
		glm::vec3 *cameraPosition = nullptr;								/**< Pointer to the position of the camera. */
		glm::quat *cameraRotation = nullptr;								/**< Pointer to the rotation of the camera. */
		bool *isOrtho = nullptr;											/**< Pointer to a boolean indicating if the camera is in orthographic mode. */
		float *fov = nullptr;												/**< Pointer to the field of view of the camera. */
		std::array<bool, MAX_LIGHT_NO> occupiedDirectionalLights = {false}; /**< Array to track occupied directional light spots. */
		std::array<bool, MAX_LIGHT_NO> occupiedPointLight = {false};		/**< Array to track occupied point light spots. */

		Shader screenShader;
		Shader skyboxShader;
		glm::vec2 customViewportSize; /**< Custom viewport size. */

		bool drawToQuad = true; /**< Flag indicating whether to draw to the quad. */

		/**
		 * @brief Constructs a Renderer object.
		 * @param ctx A pointer to the Context.
		 */
		Renderer(ContextPtr &ctx);

		/**
		 * @brief Destructs a Renderer object.
		 */
		~Renderer();

		/**
		 * @brief Renders the scene.
		 * @param ctx A pointer to the Context.
		 */
		void Render(ContextPtr &ctx);

		/**
		 * @brief Sets the viewport size.
		 * @param viewportsize The size of the viewport.
		 */
		void SetViewport(glm::vec2 viewportsize);

		// void LoadSkybox(std::array<std::filesystem::path, 6> paths);

		/**
		 * @brief Retrieves a free spot for a directional light.
		 * @param spot A pointer to the variable to store the free spot index.
		 * @return True if a free spot is available, false otherwise.
		 */
		bool GetFreeDirectionalLightSpot(unsigned int *spot);

		/**
		 * @brief Unoccupies a spot for a directional light.
		 * @param spot The spot index to unoccupy.
		 */
		void UnoccupyDirectionalLightSpot(unsigned int spot);

		/**
		 * @brief Retrieves a free spot for a point light.
		 * @param spot A pointer to the variable to store the free spot index.
		 * @return True if a free spot is available, false
		 */
		bool GetFreePointLightSpot(unsigned int *spot);

		/**
		 * @brief Unoccupies a spot for a point light.
		 * @param spot The spot index to unoccupy.
		 */
		void UnoccupyPointLightSpot(unsigned int spot);

		/**
		 * @brief Activates a shader for rendering.
		 * @param shader A pointer to the shader to activate.
		 */
		void ActivateShader(Shader *shader);

		/**
		 * @brief Callback function for handling framebuffer size changes.
		 * @param window A pointer to the GLFW window.
		 * @param width The new width of the framebuffer.
		 * @param height The new height of the framebuffer.
		 */
		static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

		IN_SERIALIZE(Renderer, drawToQuad); /**< Serialize function for Renderer. */

		friend class CameraSystem;
	};
}