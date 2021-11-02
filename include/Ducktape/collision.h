#ifndef COLLISION_H
#define COLLISION_H

class Collision : public b2RayCastCallback
{
public:
	Vector2 normal;
	GameObject* body;
	Vector2 point;
	float distance;

	float ReportFixture(b2Fixture *_fixture, const b2Vec2 &_point, const b2Vec2 &_normal, float _fraction)
	{
		point = Vector2(_point.x, _point.y);
		point = Vector2(_normal.x, _normal.y);
		distance = _fraction;
		return 0.0f;
	}
};

#endif