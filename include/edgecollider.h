#ifndef EDGECOLLIDER_H
#define EDGECOLLIDER_H

class EdgeCollider : public PhysicsScript
{
public:
    Rigidbody* rb;

    std::vector<Vector2> points;
    float density = 1.0f;
    float friction = 0.3f;
    bool isTrigger = false;
    
    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody>();
        if(rb == nullptr)
        {
            Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Collider.");
            return;
        }

        b2ChainShape chainShape;
        b2EdgeShape edgeShape;

        int size = points.size();

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
                vertices[i].Set(points[i].x, points[i].y);
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
                vertices[i].Set(points[i].x, points[i].y);
            }

            edgeShape.SetTwoSided(vertices[0], vertices[1]);
        }

        b2FixtureDef fixtureDef;
        if(points.size() > 2)
        {
            fixtureDef.shape = &chainShape;
        } 
        else
        {
            fixtureDef.shape = &edgeShape;
        }
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.isSensor = isTrigger;
        
        rb->body->CreateFixture(&fixtureDef);
    }
};

#endif