#pragma once

namespace Ducktape
{
    class Entity;

    class Scene
    {
    public:
        entt::registry sceneRegistry;

        Entity CreateEntity(const std::string& name);
        void DestroyEntity(Entity entity);
    };
}