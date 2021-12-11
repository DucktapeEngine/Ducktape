#ifndef BEHAVIOURSCRIPT_H
#define BEHAVIOURSCRIPT_H

#include "../physics/collision.h"
#include "debug.h"

namespace DT
{
    class Entity;

    class BehaviourScript
    {
    public:
        bool enabled = true;
        Entity* entity;
        bool destroyed = false;
        bool started = false;

        virtual void Start(){}
        virtual void Update(){}
        virtual void FixedUpdate(){}
        virtual void OnTransformChange(){}

        void OnRBDestroy();
        virtual void OnCollisionEnter(Collision collider){}
        virtual void OnCollisionExit(Collision collider){}

        virtual void Destroy(){}

        virtual void OnApplicationClose(){}

        void Invoke(std::string methodName, float time);

        bool operator==(BehaviourScript* script);
    };
}

#endif