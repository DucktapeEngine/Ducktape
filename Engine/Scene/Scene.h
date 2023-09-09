/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <string>
#include <iostream>
#include <array>
#include <vector>

#include <entt/entt.hpp>

#include <Core/Platform.h>
#include <Scene/System.h>
#include <Scene/Entity.h>
#include <Core/Resource.h>
#include <Core/Game.h>

namespace DT
{
    class Scene;
    class Engine;
    class Camera;

    enum RegisterAction
    {
        AddSystem,
        Assign,
        Remove
    };

    typedef void (*RegisterFunc)(Entity, Scene *, RegisterAction);

    class Scene
    {
        static inline std::unordered_map<RID, Scene *> factoryData;

    public:
        static inline std::set<Scene *> scenes;

        ContextPtr *ctx;
        entt::registry registry;
        Camera *activeCamera = nullptr;
        Entity selectedEntity = entt::null;

        json serializedData;
        bool isSerializing = true;

        Scene(RID rid, ContextPtr &ctx);
        ~Scene();

        /**
         * @brief Checks if an entity has a component of type T.
         * @tparam T The type of component to check.
         * @param entity The entity to check.
         * @return True if the entity has the component, false otherwise.
         */
        template <typename T>
        bool Has(Entity entity)
        {
            return registry.any_of<T>(entity);
        }

        /**
         * @brief Assigns a component of type T to an entity.
         * @tparam T The type of component to assign.
         * @param entity The entity to assign the component to.
         * @return A reference to the assigned component.
         */
        template <typename T>
        T &Assign(Entity entity)
        {
            if (Has<T>(entity))
                return *Get<T>(entity);

            return registry.emplace<T>(entity);
        }

        /**
         * @brief Retrieves a pointer to a component of type T for an entity.
         * @tparam T The type of component to retrieve.
         * @param entity The entity to retrieve the component from.
         * @return A pointer to the component, or nullptr if the entity does not have the component.
         */
        template <typename T>
        T *Get(Entity entity)
        {
            if (Has<T>(entity))
                return &registry.get<T>(entity);
            else
                return nullptr;
        }

        /**
         * @brief Removes a component of type T from an entity.
         * @tparam T The type of component to remove.
         * @param entity The entity to remove the component from.
         */
        template <typename T>
        void Remove(Entity entity)
        {
            if (Has<T>(entity))
            {
                // sceneRegistry.get<T>(entity).Destroy(); //TOFIX: Destroy currently not called
                registry.remove<T>(entity);
            }
        }

        /**
         * @brief Creates a view of entities with the specified components.
         * @tparam Components The types of components to include in the view.
         * @return A view of entities with the specified components.
         */
        template <typename... Components>
        auto View()
        {
            return registry.view<Components...>();
        }

        /**
         * @brief Retrieves the entity from a component and scene.
         * @tparam T The type of the component.
         * @param component The component instance.
         * @param scene The scene containing the component.
         * @return The entity associated with the component in the scene.
         */
        template <typename T>
        static Entity From(T &component, Scene &scene)
        {
            return entt::to_entity(scene.registry, component);
        }

        /**
         * @brief Serializes or deserializes a component of type T for an entity in the scene.
         * @tparam T The type of the component to serialize or deserialize.
         * @param componentName The name of the component.
         * @param entity The entity to serialize or deserialize the component for.
         * @param scene The scene containing the entity and component.
         */
        template <typename T>
        void SerializeComponent(const std::string componentName, Entity entity, Scene &scene)
        {
            try
            {
                T *component = scene.Get<T>(entity);
                if (component == nullptr)
                    return;

                if (isSerializing)
                    serializedData["entities"][entt::to_integral(entity)]["components"][componentName] = *component;
                else
                    *component = serializedData["entities"][entt::to_integral(entity)]["components"][componentName];
            }
            catch (json::exception &e)
            {
                std::cout << "[ERR] [JSON] " << e.what() << std::endl;
            }
        }

        /**
         * @brief Creates a new entity in the scene.
         * @return The newly created entity.
         */
        Entity CreateEntity();

        /**
         * @brief Destroys an entity in the scene.
         * @param entity The entity to destroy.
         */
        void DestroyEntity(Entity entity);

        /**
         * @brief Assigns a name to an entity.
         * @param entity The entity to assign the name to.
         * @param name The name to assign to the entity.
         */
        void Assign(Entity entity, const std::string &name, ContextPtr &ctx);

        /**
         * @brief Removes the name assigned to an entity.
         * @param entity The entity to remove the name from.
         * @param name The name to remove from the entity.
         */
        void Remove(Entity entity, const std::string &name, ContextPtr &ctx);

        /**
         * @brief Loads a scene resource from the given resource ID.
         * @param rid The resource ID of the scene.
         * @return A pointer to the loaded scene resource.
         */
        static Scene *LoadResource(RID rid, ContextPtr &ctx);

        /**
         * @brief Unloads a scene resource with the given resource ID.
         * @param rid The resource ID of the scene to unload.
         */
        static void UnLoadResource(RID rid);

        /**
         * @brief Retrieves the scene associated with the given entt::registry instance.
         * @param registry The entt::registry instance.
         * @return A pointer to the Scene object associated with the registry.
         */
        static Scene *GetSceneFromRegistry(entt::registry &registry);
    };

    // void to_json(json &json, Scene &scene);
    // void from_json(const json &j, Scene &scene);
}