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
	float yaw = 0.f, pitch = 0.f;

	void Tick()
	{
		// Move
		const float cameraSpeed = 2.5f * Time::deltaTime;

		if (Input::GetKey(KEY_W))
			Camera::transform.position += cameraSpeed * Camera::transform.Forward();
		if (Input::GetKey(KEY_S))
			Camera::transform.position -= cameraSpeed * Camera::transform.Forward();
		if (Input::GetKey(KEY_A))
			Camera::transform.position += cameraSpeed * Camera::transform.Right();
		if (Input::GetKey(KEY_D))
			Camera::transform.position -= cameraSpeed * Camera::transform.Right();

		// Look
		float sensitivity = 25.f * Time::deltaTime;

		yaw += -Input::mouseDelta.x * sensitivity;
		pitch += Input::mouseDelta.y * sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		ImGui::Begin("Player Controller");
		{
			ImGui::InputFloat("Yaw", &yaw);
			ImGui::InputFloat("Pitch", &pitch);
		}
		ImGui::End();

		if (Editor::mouseLock)
			Camera::transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
	}

	void OnGUI()
	{
		if (ImGui::CollapsingHeader("PlayerController"))
		{
			ImGui::DragFloat("yaw", &yaw, 0.1f, 0.0f, 360.0f);
			ImGui::DragFloat("pitch", &pitch, 0.1f, 0.0f, 360.0f);
		}
	}
};

void MainScene(Scene &scene)
{
	scene.Call<Tag>();
	scene.Call<Transform>();
	scene.Call<ModelRenderer>();
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
		player.AddComponent<Tag>().name = "Player";
		player.AddComponent<Transform>();
		player.AddComponent<PlayerController>();

		// Entity light = mainScene.CreateEntity();
		// light.AddComponent<Tag>().name = "Light";
		// light.AddComponent<Transform>();

		Entity bag = mainScene.CreateEntity();
		bag.AddComponent<Tag>().name = "Bag";
		bag.AddComponent<Transform>();
		bag.AddComponent<ModelRenderer>().path = "../resources/models/backpack/backpack.obj";

		Engine::Run(mainScene);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}