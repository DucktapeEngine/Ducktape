#ifndef SCENE_H
#define SCENE_H

#include "vector2.h"
#include <vector>

namespace DT
{
	class Entity;

	class Scene
	{
	public:
		std::vector<Entity*> entities;

		virtual void Initialize(){}

		void Destroy();
	};
}

#endif