#include "dt_time.h"
using namespace DT;

float Time::deltaTime;
sf::Clock Time::clock;
sf::Clock Time::deltaClock;

void Time::Update()
{
	Time::deltaTime = Time::deltaClock.restart().asSeconds();
}