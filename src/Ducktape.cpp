#include "Ducktape.h"

using namespace std;
using namespace Ducktape;

int main()
{
	// Application::run(); // When Working on Graphics

	Scene mainScene;
	Entity *player = mainScene.CreateEntity("Player");
	Transform *transform = player->AddComponent<Transform>();
	transform->position = Vec3f({0.0f, 0.0f, 0.0f});
}