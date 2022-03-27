#pragma once

namespace Ducktape
{
    class Transform
    {
    public:
        Transform() = default;
        Transform(const Transform &) = default;

        Vec3f position;
        Vec3f rotation;
        Vec3f scale;
    };
}