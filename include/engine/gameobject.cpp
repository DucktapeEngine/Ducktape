#include "gameobject.h"
using namespace DT;

GameObject::GameObject()
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New GameObject";
    transform = this->AddComponent<Transform>();
}

GameObject::GameObject(std::string _name)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = _name;
    transform = this->AddComponent<Transform>();
}

GameObject::GameObject(Vector2 pos, float rot, Vector2 scl)
{
    isActive = true;
    layer = 0;
    tag = "Default";
    name = "New GameObject";
    transform = this->AddComponent<Transform>();
    transform->SetPosition(pos);
    transform->SetRotation(rot);
    transform->SetScale(scl);
}

GameObject::GameObject(std::string _name, Vector2 pos, float rot, Vector2 scl)
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

GameObject* GameObject::Find(std::string _name)
{
    for(int i=0,n=SceneManager::currentScene->gameObjects.size();i<n;i++)
    {
        if(SceneManager::currentScene->gameObjects[i]->name == _name)
        {
            return SceneManager::currentScene->gameObjects[i];
        }
    }
    Debug::LogError("GameObject with name \"" + _name +"\" doesn't exist!");
    return nullptr;
}

GameObject* GameObject::Instantiate(std::string _name)
{
    SceneManager::currentScene->gameObjects.push_back(new GameObject(_name));
    return SceneManager::currentScene->gameObjects[SceneManager::currentScene->gameObjects.size()-1];
}

GameObject* GameObject::Instantiate(Vector2 pos, float rot, Vector2 scl)
{
    SceneManager::currentScene->gameObjects.push_back(new GameObject(pos, rot, scl));
    return SceneManager::currentScene->gameObjects[SceneManager::currentScene->gameObjects.size()-1];
}

GameObject* GameObject::Instantiate(std::string _name, Vector2 pos, float rot, Vector2 scl)
{
    SceneManager::currentScene->gameObjects.push_back(new GameObject(_name, pos, rot, scl));
    return SceneManager::currentScene->gameObjects[SceneManager::currentScene->gameObjects.size()-1];
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
    for(BehaviourScript* bs:gameObject->components)
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
    for(BehaviourScript* bs:gameObject->components)
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
    for(BehaviourScript* bs:gameObject->components)
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
    for(BehaviourScript* bs:gameObject->components)
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
    for(BehaviourScript* bs:gameObject->components)
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
    for(BehaviourScript* bs:gameObject->components)
    {
        if(bs != nullptr)
        {
            bs->OnTransformChange();
        }
    }
    RecalculateWorldValues();
    return _scl;
}