#ifndef RIGIDBODY2D_H
#define RIGIDBODY2D_H

class Rigidbody2D : public BaseScript
{
public:
    float gravityScale = 1.0;
    std::string type;
    bool isTrigger = false;
    b2Body* body;

    float linearDamping = 0.0f;
    float angularDamping = 0.01f;
    bool allowSleep = true;
    bool continousCollision = false;

    void Start()
    {
        b2BodyDef bodyDef;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(gameObject);
        bodyDef.position.Set(gameObject->transform->GetPosition().x, gameObject->transform->GetPosition().y);

        if(type == "dynamic")
        {
            bodyDef.type = b2_dynamicBody;
        } 
        else if(type == "kinematic")
        {
            bodyDef.type = b2_kinematicBody;
        }
        else
        {
            bodyDef.type = b2_staticBody;
        }
        body = Physics::physicsWorld.CreateBody(&bodyDef);
        
        body->SetAwake(true);

        body->SetLinearDamping(linearDamping);
        body->SetAngularDamping(angularDamping);
        body->SetSleepingAllowed(allowSleep);
        body->SetBullet(continousCollision);
    }

    void Update()
    {
        gameObject->transform->SetPosition(Vector2(body->GetPosition().x, body->GetPosition().y));
        gameObject->transform->SetRotation(body->GetAngle());
        SetVelocity(Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity * gravityScale);
    }

    void OnTransformChange()
    {
        body->SetTransform(b2Vec2(gameObject->transform->GetPosition().x, gameObject->transform->GetPosition().y), gameObject->transform->GetRotation());
    }

    Vector2 GetVelocity()
    {
        return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    }

    Vector2 SetVelocity(Vector2 _vel)
    {
        body->SetLinearVelocity(b2Vec2(_vel.x, _vel.y));
        return _vel;
    }
    
    void AddForce(Vector2 direction)
    {
        body->ApplyForceToCenter(direction.ToBox2DVector(), true);
    }

    void AddForceAtPoint(Vector2 direction, Vector2 point)
    {
        body->ApplyForce(direction.ToBox2DVector(), point.ToBox2DVector(), true);
    }

    void AddTorque(float torque)
    {
        body->ApplyTorque(torque, true);
    }

    template <typename T>
    void DestroyJoint()
    {
        T* component = gameObject->GetComponent<T>();
        if(component != nullptr)
        {
            component->Destroy();
        }
    }

    void Destroy()
    {
        if(body != nullptr && !destroyed)
        {
            DestroyJoint<RevoluteJoint2D>();
            DestroyJoint<DistanceJoint2D>();
            DestroyJoint<PrismaticJoint2D>();
            DestroyJoint<WeldJoint2D>();
            DestroyJoint<PulleyJoint2D>();
            DestroyJoint<FrictionJoint2D>();

            Physics::physicsWorld.DestroyBody(body);
            destroyed = true;
            body = nullptr;
        } 
        else 
        {
            Debug::LogError("You cannot delete an already deleted body.");
        }
        delete this;
    }
};

#endif