#include "random.h"
using namespace DT;

float Random::Range(float min, float max)
{
	int range = max - min + 1;
	return (rand() % range + min);
}