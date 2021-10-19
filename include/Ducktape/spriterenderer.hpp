#pragma once
#include <string>
#include "behaviourscript.hpp"

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;
        
        void Update();
};