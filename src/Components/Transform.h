#pragma once

namespace Ducktape
{
    class Transform
    {
    public:
        Transform() = default;
        Transform(const Transform &) = default;

        vec3 position;
        vec3 rotation;
        vec3 scale;
    };
}