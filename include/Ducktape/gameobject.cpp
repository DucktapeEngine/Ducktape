#include "gameobject.hpp"
#include "transform.hpp"
#include <string>
#include <vector>
#include "debug.hpp"
#include "scene.hpp"
#include "behaviourscript.hpp"

GameObject::GameObject()
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New GameObject";
    transform = this->AddComponent<Transform>(new Transform());
}

GameObject::GameObject(std::string _name)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
    transform = this->AddComponent<Transform>(new Transform());
}

GameObject::GameObject(Vector2 pos, float rot, Vector2 scl)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New GameObject";
    transform = this->AddComponent<Transform>(new Transform());
    transform->position = pos;
    transform->rotation = rot;
    transform->scale = scl;
}

GameObject::GameObject(std::string _name, Vector2 pos, float rot, Vector2 scl)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
    transform = this->AddComponent<Transform>(new Transform());
    transform->position = pos;
    transform->rotation = rot;
    transform->scale = scl;
}