#pragma once

class Box 
{
public:
    Vector2 scale = Vector2(1.0, 1.0);
};

class Polygon 
{
public:
    std::vector<Vector2>points;
};

class Circle
{
public:
    float radius = 1.0f;
};

class Edge
{
public:
    std::vector<Vector2>points;
};

class Rigidbody : public BehaviourScript
{
    public:
        Vector2 velocity;
        float gravityScale = 1.0;
        std::string type;
        std::string colliderType;
        bool isTrigger = false;
        b2Body* body;

        Box boxCollider;
        Polygon polygonCollider;
        Circle circleCollider;
        Edge edgeCollider;

        void Start()
        {
            UpdateCollider(colliderType);
        }

        void Update()
        {
            velocity = Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity;
        }

        void MidUpdate()
        {
            body->SetTransform(b2Vec2(gameObject->transform->position.x, gameObject->transform->position.y), gameObject->transform->rotation);
            body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
        }

        void LateUpdate()
        {
            gameObject->transform->position = Vector2(body->GetPosition().x, body->GetPosition().y);
            gameObject->transform->rotation = body->GetAngle();
            velocity = Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
        }

        void UpdateCollider(std::string _colliderType)
        {
            colliderType = _colliderType;

            b2BodyDef groundBodyDef;
            if(type == "dynamic")
            {
                groundBodyDef.type = b2_dynamicBody;
            }
            body = Physics::physicsWorld.CreateBody(&groundBodyDef);
            
            body->SetAwake(true);

            b2MassData* data;
            body->GetMassData(data);
            data->center.Set(0, 0);
            body->SetMassData(data);
            
            b2PolygonShape collisionShape;
            b2CircleShape circleShape;
            b2ChainShape chainShape;
            b2EdgeShape edgeShape;

            if(colliderType == "none")
            {
                return;
            }
            else if(colliderType == "box")
            {
                collisionShape.SetAsBox(boxCollider.scale.x * gameObject->transform->scale.x, boxCollider.scale.y * gameObject->transform->scale.y);
            }
            else if(colliderType == "circle")
            {
                circleShape.m_p.Set(0.0f, 0.0f);
                circleShape.m_radius = circleCollider.radius;
            }
            else if(colliderType == "edge")
            {
                int size = edgeCollider.points.size();

                if(size > 2)
                {
                    if(size > 8)
                    {
                        Debug::LogError("The number of vertices in a edgeCollider must be <= 8, the number of vertices chosen is " + std::to_string(size));
                        return;
                    }

                    b2Vec2 vertices[size];
                    for(int i=0,n=size;i<n;i++)
                    {
                        vertices[i].Set(edgeCollider.points[i].x, edgeCollider.points[i].y);
                    }
                    chainShape.CreateLoop(vertices, size);
                }
                else
                {
                    if(size <= 0)
                    {
                        Debug::LogError("The number of vertices in a edgeCollider must be > 0, the number of vertices chosen is " + std::to_string(size));
                        return;
                    }

                    b2Vec2 vertices[size];
                    for(int i=0,n=size;i<n;i++)
                    {
                        vertices[i].Set(edgeCollider.points[i].x, edgeCollider.points[i].y);
                    }

                    edgeShape.SetTwoSided(vertices[0], vertices[1]);
                }
            }
            else
            {
                int size = edgeCollider.points.size();

                if(size < 3 || size > 8)
                {
                    Debug::LogError("The number of vertices in a polygonCollider must be >= 3 and <= 8, the number of vertices chosen is " + std::to_string(size));
                    return;
                }

                b2Vec2 vertices[size];
                for(int i=0,n=size;i<n;i++)
                {
                    vertices[i].Set(edgeCollider.points[i].x, edgeCollider.points[i].y);
                }
                collisionShape.Set(vertices, size);
            }

            b2FixtureDef fixtureDef;
            if(colliderType == "circle")
            {
                fixtureDef.shape = &circleShape;
            }
            else if(colliderType == "edge")
            {
                if(edgeCollider.points.size() > 2)
                {
                    fixtureDef.shape = &chainShape;
                } 
                else
                {
                    fixtureDef.shape = &edgeShape;
                }
            } 
            else {
                fixtureDef.shape = &collisionShape;
            }
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;
            fixtureDef.isSensor = isTrigger;

            body->CreateFixture(&fixtureDef);
        }
};
