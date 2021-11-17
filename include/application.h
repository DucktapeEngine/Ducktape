#ifndef APPLICATION_H
#define APPLICATION_H

namespace Application 
{
	Vector2 resolution = Vector2(0, 0);
	sf::View view = sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y));
	sf::RenderWindow renderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Flappy Duck", sf::Style::Default);
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
	    if(ProjectSettings::resolution.x != 0)
	    {
		    SetResolution(ProjectSettings::resolution);
	    }
	}

	bool IsOpen()
	{
	    return renderWindow.isOpen();
	}
}

#endif