#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameobject.h"

class GameObject;

class Component 
{
    public:
        GameObject* gameObject;
};


#endif