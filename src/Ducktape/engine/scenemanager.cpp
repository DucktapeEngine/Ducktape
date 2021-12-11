#include "scenemanager.h"
using namespace DT;

Scene* SceneManager::currentScene;

void SceneManager::LoadScene(Scene* _scene)
{
    if(SceneManager::currentScene != nullptr)
    {
        SceneManager::currentScene->Destroy();
    }
    SceneManager::currentScene = _scene;
    SceneManager::currentScene->Initialize();
}