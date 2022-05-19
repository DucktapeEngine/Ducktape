/*
MIT License

Copyright (c) 2022 Ducktape

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

#define FUNCTION_TRACE
#include "Ducktape.h"

using namespace std;
using namespace Ducktape;

void MainScene(Scene &scene)
{
	scene.Call<Tag>();
	scene.Call<Transform>();
	scene.Call<Camera>();
	scene.Call<SpriteRenderer>();
}

int main()
{
	try
	{
		Engine game;
		game.configuration.windowSize = {800, 600};
		game.configuration.windowTitle = "DucktapeTest";

		Scene mainScene = Scene(MainScene);

		Entity camera = mainScene.CreateEntity();
		camera.AddComponent<Tag>().name = "MainCamera";
		camera.AddComponent<Transform>();
		camera.AddComponent<Camera>();

		Entity player = mainScene.CreateEntity();
		player.AddComponent<Tag>().name = "Player";
		player.AddComponent<Transform>();

		SpriteRenderer &sr = player.AddComponent<SpriteRenderer>();
		sr.sprite = "../sprites/ducktapeicon.png";

		game.Run(mainScene);
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
		exit(1);
	}
}