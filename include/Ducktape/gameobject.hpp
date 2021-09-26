#pragma once

class GameObject
{
    public:
        bool isActive = true;
        int layer = 0;
        Scene scene;
        std::string name = "New GameObject";
        std::string tag = "Default";
        // Transform transform;
        std::vector<BehaviourScript*> components;

        GameObject()
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = "New GameObject";
        }

        GameObject(std::string _name)
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = _name;
        }

        BehaviourScript* AddComponent(BehaviourScript* script)
        {
            components.push_back(script);
            components[components.size()-1]->gameObject = this;
            return components[components.size()-1];
        }

        template <typename T>
        T* GetComponent() 
        {
          for(auto script:components) 
          {
            if(T *ptr = dynamic_cast<T *>(script)) 
            {
              return ptr;
            }
          }
          Debug::LogWarning(std::string("Component ") + typeid(T).name() + " not found!");
          return nullptr;
        }
};