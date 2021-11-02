#ifndef COLLISION_H
#define COLLISION_H

struct Collision
{
	Vector2 normal;
	GameObject* object;

	Collision(GameObject* _object)
	{
		object = _object;
	}
};

#endif