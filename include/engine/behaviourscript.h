#ifndef BEHAVIOUR_SCRIPT_H
#define BEHAVIOUR_SCRIPT_H

class BehaviourScript
{
public:
    bool enabled = true;
    GameObject* gameObject;
    bool destroyed = false;
    bool started = false;

    virtual void Start(){}
    virtual void Update(){}
    virtual void FixedUpdate(){}
    virtual void OnTransformChange(){}
    virtual void OnCollisionEnter(Collision collider){}
    virtual void OnCollisionExit(Collision collider){}

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