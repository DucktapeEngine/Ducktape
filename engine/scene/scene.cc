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

#include <scene/scene.h>
#include <components/tag.h>
#include <core/module.h>

typedef std::shared_ptr<DT::Component> (*GetInstanceOfFunc)(DT::Context *ctx);
typedef std::type_index (*GetTypeIndexOfFunc)();

namespace DT
{
    Scene::Scene(Context &ctx) : context(ctx)
    {
        gameModule = context.GetService<Module>();
    }

    bool Scene::Has(const std::string &type, Entity entity)
    {
        std::type_index typeId = GetTypeIndexOfComponent(type);
        return components.at(entity).find(typeId) != components.at(entity).end();
    }

    std::shared_ptr<Component> Scene::Assign(const std::string &type, Entity entity)
    {
        GetInstanceOfFunc getInstanceFunc = gameModule->GetSymbolAddress<GetInstanceOfFunc>("GetInstanceOf" + type);
        std::shared_ptr<Component> component = getInstanceFunc(&context);

        std::type_index typeId = GetTypeIndexOfComponent(type);

        component->entity = entity;
        component->scene = this;
        components.at(entity)[typeId].reset(component.get());

        return component;
    }

    std::unordered_set<Entity> Scene::GetEntities()
    {
        std::unordered_set<Entity> entities;
        for (std::pair<const DT::Entity, std::unordered_map<std::type_index, std::shared_ptr<DT::Component>>> &entity : components)
        {
            entities.insert(entity.first);
        }
        return entities;
    }

    std::unordered_map<std::type_index, std::shared_ptr<Component>> Scene::View(Entity entity)
    {
        return components.at(entity);
    }

    std::type_index Scene::GetTypeIndexOfComponent(const std::string &type)
    {
        GetTypeIndexOfFunc getTypeIdFunc = gameModule->GetSymbolAddress<GetTypeIndexOfFunc>("GetTypeIndexOf" + type);
        return getTypeIdFunc();
    }
}