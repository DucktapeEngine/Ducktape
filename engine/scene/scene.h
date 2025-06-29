/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

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

#include <scene/component.h>
#include <scene/entity.h>

namespace DT
{
    class Module;

    class Scene
    {
    public:
        Scene(Context &ctx);

        std::unordered_set<Entity> GetEntities();
        std::unordered_map<std::type_index, std::shared_ptr<Component>> View(Entity entity);

        bool IsValid(Entity entity)
        {
            return tombStones.find(entity) == tombStones.end() && entity != 0;
        }

        Entity CreateEntity()
        {
            components.insert(std::make_pair(entityCounter, std::unordered_map<std::type_index, std::shared_ptr<Component>>()));
            return entityCounter++;
        }

        void DestroyEntity(Entity entity)
        {
            if (!IsValid(entity))
                return;

            auto entityComponentsItr = components.find(entity);
            if (entityComponentsItr != components.end())
                components.erase(entityComponentsItr);
            tombStones.insert(entity);
        }

        bool Has(const std::string &type, Entity entity);
        std::shared_ptr<Component> Assign(const std::string &type, Entity entity);

        template <typename T>
        bool Has(Entity entity)
        {
            auto entityComponentsItr = components.find(entity);
            if (entityComponentsItr == components.end())
                return false;

            auto &componentMap = entityComponentsItr->second;
            auto typeIndex = std::type_index(typeid(T));

            return componentMap.find(typeIndex) != componentMap.end();
        }

        template <typename T>
        std::shared_ptr<T> Require(Entity entity)
        {
            if (Has<T>(entity))
                return Get<T>(entity);
            return Assign<T>(entity);
        }

        template <typename T>
        std::shared_ptr<T> Assign(Entity entity)
        {
            std::shared_ptr<T> component = std::make_shared<T>(&context);
            component->entity = entity;
            component->scene = this;
            components.at(entity)[std::type_index(typeid(T))] = component;

            return component;
        }

        template <typename T>
        std::shared_ptr<T> Get(Entity entity)
        {
            return std::static_pointer_cast<T>(components.at(entity).at(std::type_index(typeid(T))));
        }

        template <typename T>
        void Remove(Entity entity)
        {
            if (Has<T>(entity))
                components[entity][std::type_index(typeid(T))] = nullptr;
        }

    private:
        Entity entityCounter = 1;
        std::unordered_set<Entity> tombStones;
        std::unordered_map<Entity, std::unordered_map<std::type_index, std::shared_ptr<Component>>> components;
        Module *gameModule;
        Context &context;

        std::type_index GetTypeIndexOfComponent(const std::string &type);
    };
}
