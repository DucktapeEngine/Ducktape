#include "behaviourscript.hpp"
#include "component.hpp"
#include "debug.hpp"

void BehaviourScript::Invoke(std::string methodName, float time)
{
    Debug::LogWarning("Invoke not Implemented yet.");
}

bool BehaviourScript::operator==(BehaviourScript script)
{
    if (enabled == script.enabled && gameObject == script.gameObject && gameObject->transform == script.gameObject->transform)
    {
        return true;
    }
    return false;
}