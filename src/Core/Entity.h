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

        operator entt::entity() const { return handle; }
        operator bool() const { return handle != entt::null; }

        template <typename T>
        bool HasComponent()
        {
            return scene->sceneRegistry.any_of<T>(handle);
        }

        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            DT_ASSERT(!HasComponent<T>(), "Entity already has component.");
            
            return scene->sceneRegistry.emplace<T>(handle, std::forward<Args>(args)...);
        }

        template <typename T>
        T &GetComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");
            return scene->sceneRegistry.get<T>(handle);
        }

        template <typename T>
        void RemoveComponent()
        {
            DT_ASSERT(HasComponent<T>(), "Entity does not have component.");
            scene->sceneRegistry.remove<T>(handle);
        }
    };

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = Entity(sceneRegistry.create(), this);

        entity.AddComponent<Transform>();
        Tag& tag = entity.AddComponent<Tag>();
        

        if (tag.name.empty())
        {
            tag.name = name;
        }
        else
        {
            tag.name = "Unnamed Entity";
        }
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        sceneRegistry.destroy(entity.handle);
    }
}