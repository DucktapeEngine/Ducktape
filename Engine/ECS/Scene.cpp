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

#include <ECS/Scene.h>
#include <Components/Tag.h>
#include <Core/Module.h>

typedef std::shared_ptr<DT::Component>(*GetInstanceOfFunc)(DT::Context *ctx);
typedef std::type_index(*GetTypeIndexOfFunc)();

namespace DT
{
    Scene::Scene(Context &ctx) : context(ctx)
    {
        PROFILE();

        gameModule = context.GetService<Module>().Fatal("Scene::Scene()");
    }

    ErrorOr<bool> Scene::Has(const std::string &type, Entity entity)
    {
        PROFILE();

        ErrorOr<std::type_index> typeId = GetTypeIndexOfComponent(type);
        if (typeId.HasError())
            return ErrorOr<bool>(typeId.GetError());

        return components.at(entity).find(typeId.GetValue()) != components.at(entity).end();
    }

    ErrorOr<std::shared_ptr<Component>> Scene::Assign(const std::string &type, Entity entity)
    {
        PROFILE();

        if (!IsValid(entity))
            return ErrorOr<std::shared_ptr<Component>>("Invalid entity.\n");

        ErrorOr<bool> hasComponent = Has(type, entity);
        if (hasComponent.HasError())
            return ErrorOr<std::shared_ptr<Component>>(hasComponent.GetError());
        if (hasComponent.GetValue())
            return ErrorOr<std::shared_ptr<Component>>("Entity has already been assigned " + type + ".\n");

        ErrorOr<GetInstanceOfFunc> getInstanceFunc = gameModule->GetSymbolAddress<GetInstanceOfFunc>("GetInstanceOf" + type);
        if (getInstanceFunc.HasError())
            return ErrorOr<std::shared_ptr<Component>>(getInstanceFunc.GetError());
        std::shared_ptr<Component> component = getInstanceFunc.GetValue()(&context);

        ErrorOr<std::type_index> typeId = GetTypeIndexOfComponent(type);
        if (typeId.HasError())
            return ErrorOr<std::shared_ptr<Component>>(typeId.GetError());

        component->entity = entity;
        component->scene = this;
        components.at(entity)[typeId.GetValue()].reset(component.get());

        return component;
    }

    std::unordered_set<Entity> Scene::GetEntities()
    {
        PROFILE();

        std::unordered_set<Entity> entities;
        for (std::pair<const DT::Entity, std::unordered_map<std::type_index, std::shared_ptr<DT::Component>>> &entity : components)
        {
            entities.insert(entity.first);
        }
        return entities;
    }

    ErrorOr<std::unordered_map<std::type_index, std::shared_ptr<Component>>> Scene::View(Entity entity)
    {
        PROFILE();

        if (!IsValid(entity))
            return ErrorOr<std::unordered_map<std::type_index, std::shared_ptr<Component>>>("Invalid entity.\n");
        return components.at(entity);
    }

    ErrorOr<Entity> Scene::GetEntityNamed(const std::string &name)
    {
        for (Entity entity : GetEntities())
            if (Has<Tag>(entity))
                if (Get<Tag>(entity).Fatal("Scene::GetEntityWithName()")->name == name)
                    return entity;
        return ErrorOr<Entity>("No entity named " + name + ".\n");
    }
    
    ErrorOr<std::type_index> Scene::GetTypeIndexOfComponent(const std::string &type)
    {
        ErrorOr<GetTypeIndexOfFunc> getTypeIdFunc = gameModule->GetSymbolAddress<GetTypeIndexOfFunc>("GetTypeIndexOf" + type);
        if (getTypeIdFunc.HasError())
            return ErrorOr<std::type_index>(getTypeIdFunc.GetError());
        return getTypeIdFunc.GetValue()();
    }
}