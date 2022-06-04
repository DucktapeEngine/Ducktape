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

#define FUNCTION_TRACE
#include <Ducktape.h>

using namespace DT;

class PlayerController : public Component
{
public:
	float yaw, pitch;

	void Init()
	{
		Camera::transform.position = {0.0f, 0.0f, 3.0f};
		Camera::transform.rotation = {0.0f, 0.0f, -1.0f};

		glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Tick()
	{
		// Move
		const float cameraSpeed = 2.5f * Time::deltaTime;

		if (glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS)
			Camera::transform.position += cameraSpeed * Camera::transform.rotation;
		if (glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS)
			Camera::transform.position -= cameraSpeed * Camera::transform.rotation;
		if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS)
			Camera::transform.position -= glm::normalize(glm::cross(Camera::transform.rotation, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
		if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS)
			Camera::transform.position += glm::normalize(glm::cross(Camera::transform.rotation, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;

		// Look
		float sensitivity = 1.0f * Time::deltaTime;

		yaw += Input::mouseDelta.x;
		pitch += Input::mouseDelta.y;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		Camera::transform.SetEulerAngles({yaw, pitch, 0.0f});
	}
};

void MainScene(Scene &scene)
{
	scene.Call<Tag>();
	scene.Call<Transform>();
	scene.Call<PlayerController>();
}

int main()
{
	try
	{
		std::cout << "Ducktape  Copyright (C) 2022  Aryan Baburajan\n"
					 "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
					 "This is free software, and you are welcome to redistribute it\n"
					 "under certain conditions; type `show c' for details.\n";

		Configuration::windowSize = {800, 600};
		Configuration::windowTitle = "DucktapeTest";

		Scene mainScene = Scene(MainScene);

		Entity player = mainScene.CreateEntity();
		player.AddComponent<Tag>();
		player.AddComponent<Transform>();
		player.AddComponent<PlayerController>();

		Engine::Run(mainScene);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}