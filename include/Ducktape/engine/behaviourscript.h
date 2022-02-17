/*
MIT License

Copyright (c) 2022 Ducktape

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

#ifndef DUCKTAPE_ENGINE_BEHAVIOURSCRIPT_H_
#define DUCKTAPE_ENGINE_BEHAVIOURSCRIPT_H_

#include <vector>

#include <Ducktape/physics/collision.h>
#include <Ducktape/engine/debug.h>

namespace DT
{
    class Entity;

    /**
     * @brief Base class for components that are to be attached to entities.
     *
     * Components are essentially what add scripting functionality to the engine. You may attach any number of components to an entity. Components are executed in the order of attachment.

     * Scripting a component is done through creating a class that inherits from the `BehaviourScript` like:
     * ```cpp
     * class SomeComponent : public DT::BehaviourScript {
     * };```
     *
     * Through inheritance, the engine lets you override various methods, primarily `BehaviourScript::Init()` and `BehaviourScript::Tick()`.
     * So what's the purpose of all this?
     * `BehaviourScript::Init()` is called at the start of every scene, and `BehavourScript::Tick()` is called on every frame. And thus overriding these methods will let you, well, execute code at the start of every scene, and every frame. Ducktape's scripting is similar to that of Unity's, so if you have past experience with Unity's scripting before, this should be familiar to you. `BehaviourScript` being `MonoBehavour`, `Init()` being `Start()`, and `Tick()` being `Update()`.
     *
     * You may add a component to an Entity using `Entity::AddComponent()`. This method returns a pointer to the component, so you may store it in a variable and thus modify the properties of other components.
     *
     * Example:
     *
     * ```cpp
     * // Creating a component to control our player based on input
     * class PlayerController : public BehaviourScript
     * {
     * public:
     *     float playerSpeed = 10.0f;
     *
     *     // Called at the start of the scene
     *     void Init()
     *     {
     *
     *     }
     *
     *     // Called every frame
     *     void Tick()
     *     {
     *         // Handle player movement here or something
     *     }
     * };
     *
     * class SampleScene : public Scene {
     * public:
     *     void Init()
     *     {
     *         // Create a new entity
     *         Entity* player = Entity::Instantiate("Player");
     *
     *         // Add the player component to the entity
     *         PlayerController* playerController = player->AddComponent<PlayerController>();
     *     }
     * };
     * ```
     *
     * Other than `BehaviourScript::Init()` and `BehaviourScript::Tick()`, there are other methods too. Check the virtual function list for the `BehaviourScript` class to see what else you can override.
     *
     * Fun fact:
     * All components like `SpriteRenderer`, `Rigidbody`, etc. are all components scripted like this. :)
     * Now hopefully this should've given you an idea of how to use components in Ducktape.
     * Cheers!
     */
    class BehaviourScript
    {
    public:
        /**
         * @brief The entity this component is attached to.
         */
        Entity *entity;

        /**
         * @brief If the component is enabled or not. You may enable/disable components
         * using the BehaviourScript::setEnabled() method.
         */
        bool isEnabled = true;

        /**
         * @brief If the component has been destroyed yet using BehaviourScript::destroy();
         */
        bool isDestroyed = false;

        /**
         * @brief Called when the component is added to an entity.
         *
         * NOTE: This method MUST be used rather than the default BehaviourScript::BehaviourScript() constructor.
         */
        virtual void Constructor(){};

        /**
         * @brief Called at the start of the project.
         */
        virtual void Init() {}

        /**
         * @brief Called on every frame.
         */
        virtual void Tick() {}

        /**
         * @brief Triggered when the Rigidbody attached to this component enters a collision.
         *
         * @param collider Collider containing information about the collision.
         */
        virtual void OnCollisionEnter(Collision collider) {}

        /**
         * @brief Triggered when the Rigidbody attached to this component exits a collision.
         *
         * @param collider Collider containing information about the collision.
         */
        virtual void OnCollisionExit(Collision collider) {}

        /**
         * @brief Triggered when this component is enabled using BehaviourScript::setEnabled().
         */
        virtual void OnEnable() {}

        /**
         * @brief Triggered when this component is disabled using BehaviourScript::setEnabled().
         */
        virtual void OnDisable() {}

        /**
         * @brief Enable/Disable this component.
         *
         * @param enabled If the component should be enabled or not.
         */
        void SetEnabled(bool enabled);

        /**
         * @brief Triggered when this component is destroyed using BehaviourScript::destroy().
         */
        virtual void OnDestroy() {}

        /**
         * @brief Destroy this component.
         */
        void Destroy();

        /**
         * @brief Triggered when application is closed.
         */
        virtual void OnApplicationClose() {}
    };
}

#endif