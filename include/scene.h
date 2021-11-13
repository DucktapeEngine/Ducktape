#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	std::vector<GameObject*> gameObjects;

	virtual void Initialize(){}

	void Destroy()
	{
		gameObjects.clear();
	}

	static void LoadScene(Scene* scene);
};

#endif