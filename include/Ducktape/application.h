#ifndef APPLICATION_H
#define APPLICATION_H

namespace Application 
{
	Vector2 resolution = Vector2(800, 500);
	// The (WIDTH, HEIGHT) being 500 is temporary, the application should be running in full screen by default.
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y));
	sf::RenderWindow renderWindow(sf::VideoMode(resolution.x, resolution.y), "Flappy Duck", sf::Style::Default);
	bool isRunning = false;

	void SetResolution(Vector2 _res)
	{
		resolution = _res;
		renderWindow.setSize(sf::Vector2u(resolution.x, resolution.y));
	}

	void Initialize()
	{
	    renderWindow.setVerticalSyncEnabled(true);
	    renderWindow.setFramerateLimit(60);
	    renderWindow.setView(view);
	}

	bool IsOpen()
	{
	    return renderWindow.isOpen();
	}
}

#endif