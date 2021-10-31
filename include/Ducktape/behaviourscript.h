#ifndef BEHAVIOR_SCRIPT_H
#define BEHAVIOR_SCRIPT_H


class BehaviourScript
{
    public:
        bool enabled = true;
        GameObject* gameObject;
        bool destroyed = false;
        virtual void Start(){}
        virtual void Update(){}
        virtual void MidUpdate(){}
        virtual void LateUpdate(){}
        virtual void Destroy()
        {
            delete this;
        }
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

#endif