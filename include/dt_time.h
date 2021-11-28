#ifndef TIME_H
#define TIME_H

namespace Time 
{
	float deltaTime;
	sf::Clock clock;
    sf::Clock deltaClock;

	void Update()
	{
		Time::deltaTime = Time::deltaClock.restart().asSeconds();
	}
};

#endif