#pragma once

#include <Core/Engine.h>

namespace DT
{
    constexpr float DEG2RAD = 0.0174533f;

    class Panel{
    public:
        virtual void Start(){}
        virtual void Update(Engine &engine){}
        virtual void Destroy(){}
    };
}