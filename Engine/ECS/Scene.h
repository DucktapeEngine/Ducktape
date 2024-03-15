/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#pragma once

#include <Core/Error.h>
#include <ECS/Component.h>
#include <ECS/Entity.h>

namespace DT
{
    class Module;
    
    class Scene
    {
    public:
        Scene(Context &ctx);

        std::unordered_set<Entity> GetEntities();
        ErrorOr<std::unordered_map<std::type_index, std::shared_ptr<Component>>> View(Entity entity);
        ErrorOr<Entity> GetEntityNamed(const std::string &name);

        bool IsValid(Entity entity)
        {
            PROFILE();

            return tombStones.find(entity) == tombStones.end() && entity != 0;
        }

        Entity CreateEntity()
        {
            PROFILE();

            components.insert(std::make_pair(entityCounter, std::unordered_map<std::type_index, std::shared_ptr<Component>>()));
            return entityCounter++;
        }

        Error DestroyEntity(Entity entity)
        {
            PROFILE();

            if (!IsValid(entity))
                return Error("Invalid entity.\n");
            
            auto entityComponentsItr = components.find(entity);
            if (entityComponentsItr != components.end())
                components.erase(entityComponentsItr);
            tombStones.insert(entity);

            return Error();
        }
        
        ErrorOr<bool> Has(const std::string &type, Entity entity);
        ErrorOr<std::shared_ptr<Component>> Assign(const std::string &type, Entity entity);

        template <typename T>
        bool Has(Entity entity)
        {
            PROFILE();

            if (!IsValid(entity))
                return false;

            auto entityComponentsItr = components.find(entity);
            if (entityComponentsItr == components.end())
                return false;

            auto& componentMap = entityComponentsItr->second;
            auto typeIndex = std::type_index(typeid(T));

            return componentMap.find(typeIndex) != componentMap.end();
        }

        template <typename T>
        ErrorOr<std::shared_ptr<T>> Require(Entity entity)
        {
            PROFILE();

            if (Has<T>(entity))
                return Get<T>(entity);
            return Assign<T>(entity);
        }

        template <typename T>
        ErrorOr<std::shared_ptr<T>> Assign(Entity entity)
        {
            PROFILE();

            if (!IsValid(entity))
                return ErrorOr<std::shared_ptr<T>>("Invalid entity.\n");
            if (Has<T>(entity))
                return ErrorOr<std::shared_ptr<T>>("Entity has already been assigned " + std::string(typeid(T).name()) + ".\n");
                
            std::shared_ptr<T> component = std::make_shared<T>(&context);
            component->entity = entity;
            component->scene = this;
            components.at(entity)[std::type_index(typeid(T))] = component;
            
            return component;
        }

        template <typename T>
        ErrorOr<std::shared_ptr<T>> Get(Entity entity)
        {
            PROFILE();

            if (!IsValid(entity))
                return ErrorOr<std::shared_ptr<T>>("Invalid entity.\n");
            if (!Has<T>(entity))
                return ErrorOr<std::shared_ptr<T>>("Entity does not have component " + std::string(typeid(T).name()) + ".\n");

            return std::static_pointer_cast<T>(components.at(entity).at(std::type_index(typeid(T))));
        }

        template <typename T>
        Error Remove(Entity entity)
        {
            PROFILE();

            if (!IsValid(entity))
                return Error("Invalid entity.\n");
            if (!Has<T>(entity))
                return Error("Entity does not have component " + std::string(typeid(T).name()) + ".\n");
            
            components[entity][std::type_index(typeid(T))] = nullptr;
            return Error();
        }

    private:    
        Entity entityCounter = 1;
        std::unordered_set<Entity> tombStones;
        std::unordered_map<Entity, std::unordered_map<std::type_index, std::shared_ptr<Component>>> components;
        Module *gameModule;
        Context &context;

        ErrorOr<std::type_index> GetTypeIndexOfComponent(const std::string &type);
    };
}
