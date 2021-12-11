#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

namespace DT
{
	namespace SceneManager
	{
	    extern Scene* currentScene;

	    void LoadScene(Scene* scene);
	}
}

#endif