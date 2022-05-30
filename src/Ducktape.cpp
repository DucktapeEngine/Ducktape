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

class CamController : public Component
{
public:
	Transform *transform;

	void Init()
	{
		transform = &Entity::FromComponent(*this).GetComponent<Transform>();
	}

	void Tick()
	{
		if (Input::GetKey(KeyCode::W))
			transform->position += glm::vec2(0.f, -1.f);

		if (Input::GetKey(KeyCode::S))
			transform->position += glm::vec2(0.f, 1.f);

		if (Input::GetKey(KeyCode::A))
			transform->position += glm::vec2(-1.f, 0.f);

		if (Input::GetKey(KeyCode::D))
			transform->position += glm::vec2(1.f, 0.f);
	}
};

class PlayController : public Component
{
public:
	Transform *transform;

	void Init()
	{
		transform = &Entity::FromComponent(*this).GetComponent<Transform>();
	}

	void Tick()
	{
		if (Input::GetKey(KeyCode::Up))
			transform->position += glm::vec2(0.f, -1.f);

		if (Input::GetKey(KeyCode::Down))
			transform->position += glm::vec2(0.f, 1.f);

		if (Input::GetKey(KeyCode::Left))
			transform->position += glm::vec2(-1.f, 0.f);

		if (Input::GetKey(KeyCode::Right))
			transform->position += glm::vec2(1.f, 0.f);
	}
};

void MainScene(Scene &scene)
{
	scene.Call<Tag>();
	scene.Call<Transform>();
	scene.Call<Camera>();
	scene.Call<SpriteRenderer>();
	scene.Call<CamController>();
	scene.Call<PlayController>();
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

		Entity camera = mainScene.CreateEntity();
		camera.AddComponent<Tag>().name = "MainCamera";
		camera.AddComponent<Transform>().position = {0.f, -1.f};
		camera.AddComponent<Camera>();
		camera.AddComponent<CamController>();

		Entity player = mainScene.CreateEntity();
		player.AddComponent<Tag>().name = "Player";
		player.AddComponent<Transform>();
		SpriteRenderer &sr = player.AddComponent<SpriteRenderer>();
		sr.spritePath = "../resources/sprites/logo.png";
		sr.pixelPerUnit = 2.f;
		player.AddComponent<PlayController>();

		Engine::Run(mainScene);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}