#ifndef SCENE_H
#define SCENE_H

#include "vector2.h"
#include <vector>

namespace DT
{
	class GameObject;

	class Scene
	{
	public:
		std::vector<GameObject*> gameObjects;

		virtual void Initialize(){}

		void Destroy();
	};
}

#endif