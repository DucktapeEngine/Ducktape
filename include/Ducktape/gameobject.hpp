#pragma once

class GameObject
{
    public:
        bool isActive = true;
        int layer = 0;
        Scene scene;
        std::string name = "New GameObject";
        std::string tag = "Default";
        Transform* transform;
        std::vector<BehaviourScript*> components;

        GameObject()
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            transform = this->AddComponent<Transform>();
        }

        GameObject(std::string _name)
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = _name;
        }

        template <typename T>
        T* AddComponent()
        {
            this->components.push_back(new T());
            int size = this->components.size()-1;
            this->components[size]->gameObject = this;
            if(GetComponent<Transform>() == nullptr) std::cout<<"yes"<<std::endl;
            return (T*)this->components[size];
        }

        template <typename T>
        T* GetComponent() 
        {
          for(auto script:this->components) 
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