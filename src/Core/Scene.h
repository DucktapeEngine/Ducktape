#pragma once

namespace Ducktape
{
    class Entity;

    class Scene
    {
    public:
        entt::registry registry;
        std::vector<Entity> entities;

        Entity *CreateEntity(const std::string& name);
        Entity *CreateEntity(Entity entity);
        Entity *GetEntity(const std::string name);
        Entity *DestroyEntity(Entity* entity);
    };
}