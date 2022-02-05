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
     * You may add a component to an entity by calling Entity::AddComponent<type>() 
     * where type is the class of the component.
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
        virtual void Constructor() {};

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