#include "Ducktape.h"

using namespace std;
using namespace Ducktape;

int main()
{
	Configuration::Application::initialWindowSize = { 800, 600 };
	Configuration::Application::applicationName = "DucktapeTest";

	Scene mainScene;
	Entity player = mainScene.CreateEntity("Player");
	Transform& transform = player.GetComponent<Transform>();
	transform.position = vec3(0.0f, 0.0f, 0.0f);

	Engine::Run(mainScene);
}