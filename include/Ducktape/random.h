#ifndef RANDOM_H
#define RANDOM_H

namespace Random
{
	float Range(float min, float max)
	{
		int range = max - min + 1;
		return (rand() % range + min);
	}
}

#endif