#include "time.hpp"

void Time::Update()
{
	Time::deltaTime = Time::deltaClock.restart().asSeconds();
}