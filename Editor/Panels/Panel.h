#pragma once

#include <Core/Engine.h>
#include <Core/ImGui.h>

namespace DT
{
    constexpr float DEG2RAD = 0.0174533f;

    class Panel
    {
    public:
        virtual void Start() {}
        virtual const char* GetWindowName() { return nullptr; }
        virtual void Update(Engine &engine) {}
        virtual void Destroy(Engine &engine) {}
    };
}