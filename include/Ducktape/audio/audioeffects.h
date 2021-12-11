#ifndef AUDIOEFFECTS_H
#define AUDIOEFFECTS_H

#include "../engine/vector2.h"

namespace DT
{
    class AudioEffects
    {
    public:
        bool loop = false;
        float pitch = 1.0f;
        float volume = 100.0f;
        float distance = 1.0f;
        bool spatial = false;
        Vector2 position = Vector2(0.0f, 0.0f);    
    };
}

#endif