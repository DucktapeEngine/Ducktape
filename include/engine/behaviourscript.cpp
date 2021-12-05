#include "behaviourscript.h"
using namespace DT;

void BehaviourScript::Invoke(std::string methodName, float time)
{
    Debug::LogWarning("Invoke not Implemented yet.");
}

bool BehaviourScript::operator==(BehaviourScript* script)
{
    if(this == script)
    {
        return true;
    }
    return false;
}

void BehaviourScript::OnRBDestroy()
{
    this->Destroy();
}