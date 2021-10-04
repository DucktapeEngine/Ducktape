#pragma once

class BoxCollider2D : public BehaviourScript
{
    public:
        BoxCollider2D()
        {
            ;
        }

        Vector2 colliderScale;
        Rigidbody rb;

        void Start(UpdateEssentials* updateEssentials)
        {
            rb = gameObject.GetComponent<Rigidbody>();
            b2PolygonShape groundBox;
            groundBox.SetAsBox(colliderScale.x, colliderScale.y);

            rb.groundBody->CreateFixture(&groundBox, 0.0f);
        }

        void Update(UpdateEssentials* updateEssentials)
        {
        }
};
