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
<<<<<<< Updated upstream
            transform = this->AddComponent<Transform>();
=======
            name = "New GameObject";
            transform = this->AddComponent<Transform>(new Transform());
>>>>>>> Stashed changes
        }

        GameObject(std::string _name)
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = _name;
            transform = this->AddComponent<Transform>(new Transform());
        }

<<<<<<< Updated upstream
        template <typename T>
        T* AddComponent()
        {
            this->components.push_back(new T());
            int size = this->components.size()-1;
            this->components[size]->gameObject = this;
            if(GetComponent<Transform>() == nullptr) std::cout<<"yes"<<std::endl;
=======
        GameObject(Vector2 pos, float rot, Vector2 scl)
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = "New GameObject";
            transform = this->AddComponent<Transform>(new Transform());
            transform->position = pos;
            transform->rotation = rot;
            transform->scale = scl;
        }

        GameObject(std::string _name, Vector2 pos, float rot, Vector2 scl)
        {
            isActive = true;
            layer = 0;
            tag = "Default";
            name = _name;
            transform = this->AddComponent<Transform>(new Transform());
            transform->position = pos;
            transform->rotation = rot;
            transform->scale = scl;
        }

        template <typename T>
        T* AddComponent(BehaviourScript* script)
        {
            this->components.push_back(script);
            int size = this->components.size()-1;
            this->components[size]->gameObject = this;
>>>>>>> Stashed changes
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