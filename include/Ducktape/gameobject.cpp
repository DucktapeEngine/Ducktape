#include "gameobject.hpp"
#include "behaviourscript.hpp"

GameObject::GameObject()
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New GameObject";
}

GameObject::GameObject(std::string _name)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
}

BehaviourScript* GameObject::AddComponent(BehaviourScript* script)
{
    components.push_back(script);
    components[components.size()-1]->gameObject = this;
    return components[components.size()-1];
}


