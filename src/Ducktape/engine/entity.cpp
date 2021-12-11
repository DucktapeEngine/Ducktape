#include "entity.h"
using namespace DT;

Entity::Entity()
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New Entity";
    transform = this->AddComponent<Transform>();
}

Entity::Entity(std::string _name)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
    transform = this->AddComponent<Transform>();
}

Entity::Entity(Vector2 pos, float rot, Vector2 scl)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New Entity";
    transform = this->AddComponent<Transform>();
    transform->SetPosition(pos);
    transform->SetRotation(rot);
    transform->SetScale(scl);
}

Entity::Entity(std::string _name, Vector2 pos, float rot, Vector2 scl)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
    transform = this->AddComponent<Transform>();
    transform->SetPosition(pos);
    transform->SetRotation(rot);
    transform->SetScale(scl);
}

Entity* Entity::Find(std::string _name)
{
    for(int i=0,n=SceneManager::currentScene->entities.size();i<n;i++)
    {
        if(SceneManager::currentScene->entities[i]->name == _name)
        {
            return SceneManager::currentScene->entities[i];
        }
    }
    Debug::LogError("Entity with name \"" + _name +"\" doesn't exist!");
    return nullptr;
}

Entity* Entity::Instantiate(std::string _name)
{
    SceneManager::currentScene->entities.push_back(new Entity(_name));
    return SceneManager::currentScene->entities[SceneManager::currentScene->entities.size()-1];
}

Entity* Entity::Instantiate(Vector2 pos, float rot, Vector2 scl)
{
    SceneManager::currentScene->entities.push_back(new Entity(pos, rot, scl));
    return SceneManager::currentScene->entities[SceneManager::currentScene->entities.size()-1];
}

Entity* Entity::Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
{
    SceneManager::currentScene->entities.push_back(new Entity(_name, pos, rot, scl));
    return SceneManager::currentScene->entities[SceneManager::currentScene->entities.size()-1];
}

void Transform::RecalculateLocalValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform* currentParent = this->parent;

    while(currentParent != nullptr)
    {
        _pos = _pos + currentParent->GetLocalPosition();
        _rot = _rot + currentParent->GetLocalRotation();
        _scl = _scl + currentParent->GetLocalScale();
        currentParent = currentParent->parent;
    }

    localPosition = position - _pos;
    localRotation = rotation - _rot;
    localScale = scale - _scl;
}

void Transform::RecalculateWorldValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform* currentParent;

    while(currentParent != nullptr)
    {
        _pos = _pos + currentParent->GetLocalPosition();
        _rot = _rot + currentParent->GetLocalRotation();
        _scl = _scl + currentParent->GetLocalScale();
        currentParent = currentParent->parent;
    }

    position = _pos;
    rotation = _rot;
    scale = _scl;
}

Vector2 Transform::SetPosition(Vector2 _pos)
{
    position = _pos;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateLocalValues();
    return _pos;
}

float Transform::SetRotation(float _rot)
{
    rotation = _rot;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateLocalValues();
    return _rot;
}

Vector2 Transform::SetScale(Vector2 _scl)
{
    scale = _scl;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateLocalValues();
    return _scl;
}

Vector2 Transform::SetLocalPosition(Vector2 _pos)
{
    position = _pos;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateWorldValues();
    return _pos;
}

float Transform::SetLocalRotation(float _rot)
{
    rotation = _rot;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateWorldValues();
    return _rot;
}

Vector2 Transform::SetLocalScale(Vector2 _scl)
{
    scale = _scl;
    for(BehaviourScript* bs:entity->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateWorldValues();
    return _scl;
}