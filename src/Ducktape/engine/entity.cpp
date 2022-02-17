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

#include <Ducktape/engine/entity.h>
using namespace DT;

bool Entity::RemoveComponent(BehaviourScript *check)
{
    int i = 0;
    for (auto script : this->components)
    {
        if (script == check)
        {
            this->components.erase(this->components.begin() + i);
            return true;
        }
        i++;
    }
    return false;
}

Entity *Entity::Find(std::string entityName)
{
    for (int i = 0, n = SceneManager::currentScene->entities.size(); i < n; i++)
    {
        if (SceneManager::currentScene->entities[i]->name == entityName)
        {
            return SceneManager::currentScene->entities[i];
        }
    }
    Debug::LogError("Entity with name \"" + entityName + "\" doesn't exist!");
    return nullptr;
}

Entity *Entity::Instantiate(std::string entityName)
{
    Entity *ent = new Entity();
    ent->isEnabled = true;
    ent->name = entityName;
    ent->transform = ent->AddComponent<Transform>();
    SceneManager::currentScene->entities.push_back(ent);
    ent->scene = SceneManager::currentScene;
    Memory::heapMemory.push_back(ent);
    return ent;
}

Entity *Entity::Instantiate(std::string entityName, Vector2 pos, float rot, Vector2 scl)
{
    Entity *ent = new Entity();
    ent->isEnabled = true;
    ent->name = entityName;
    ent->transform = ent->AddComponent<Transform>();
    ent->transform->SetPosition(pos);
    ent->transform->SetRotation(rot);
    ent->transform->SetScale(scl);
    SceneManager::currentScene->entities.push_back(ent);
    ent->scene = SceneManager::currentScene;
    Memory::heapMemory.push_back(ent);
    return ent;
}

void Entity::Destroy()
{
    this->isDestroyed = true;
    for (size_t i = 0, n = SceneManager::currentScene->entities.size(); i < n; i++)
    {
        if (SceneManager::currentScene->entities[i] == this)
        {
            SceneManager::currentScene->entities.erase(SceneManager::currentScene->entities.begin() + i);
            break;
        }
    }
}

void Entity::SetEnabled(bool isEnabled)
{
    this->isEnabled = isEnabled;
}