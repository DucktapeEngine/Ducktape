#pragma once

class BehaviourScript
{
    public:
        bool enabled = true;
        GameObject* gameObject;
        virtual void Start(){}
        virtual void Update(){}
        virtual void MidUpdate(){}
        virtual void LateUpdate(){}
        void Invoke(std::string methodName, float time)
        {
            Debug::LogWarning("Invoke not Implemented yet.");
        }

        bool operator==(BehaviourScript* script)
        {
            if(this == script)
            {
                return true;
            }
            return false;
        }
};