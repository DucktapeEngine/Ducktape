#pragma once

namespace Ducktape
{
    class Entity
    {
    public:
        entt::entity handle;
        std::string name;
        Scene *scene;

        Entity() = default;
        Entity(const Entity &other) = default;

        Entity(entt::entity entityHandle, Scene *scene) : handle(entityHandle), scene(scene) {}

        operator bool() const { return handle != entt::null; }

        template <typename T>
        bool HasComponent()
        {
            return scene->registry.any_of<T>(handle);
        }

        template <typename T, typename... Args>
        T *AddComponent(Args &&...args)
        {
            DT_ASSERT(!HasComponent<T>(), "Entity already has component.");
            
            return &scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
        }

        template <typename T>
        T *GetComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");
            return &scene->registry.get<T>(handle);
        }

        template <typename T>
        void RemoveComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");
            scene->registry.remove<T>(handle);
        }
    };

    Entity *Scene::CreateEntity(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(globalMutex);

        this->entities.push_back(Entity(registry.create(), this));
        Entity *entity = &this->entities.back();

        if (name.empty())
        {
            entity->name = name;
        }
        else
        {
            entity->name = "Unnamed Entity";
        }

        entity->AddComponent<Transform>();
        return entity;
    }

    Entity *Scene::CreateEntity(Entity entity)
    {
        this->entities.push_back(entity);
        return &this->entities.back();
    }

    Entity *Scene::GetEntity(const std::string name)
    {
        for (Entity &entity : this->entities)
        {
            if (entity.name == name)
            {
                return &entity;
            }
        }

        return nullptr;
    }

    Entity *Scene::DestroyEntity(Entity* entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        for (auto it = this->entities.begin(); it != this->entities.end(); ++it)
        {
            if (&(*it) == entity)
            {
                this->registry.destroy(it->handle);
                this->entities.erase(it);
                return entity;
            }
        }

        return nullptr;
    }
}