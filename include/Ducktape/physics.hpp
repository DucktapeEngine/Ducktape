#pragma once

class Physics
{
	public:
		
		b2World* world;

<<<<<<< Updated upstream
		Physics()
		{
		    b2Vec2 b2Gravity(Gravity().x, Gravity().y);
		    b2World _world(b2Gravity);
		    world = &_world;
		}

		Vector2 Gravity(){
			return Vector2(0.0, -9.8);
=======
		Physics(b2World* _world)
		{
		    world = _world;
		}

		static Vector2 Gravity()
		{
			return Vector2(0.0, 1);
>>>>>>> Stashed changes
		}
};