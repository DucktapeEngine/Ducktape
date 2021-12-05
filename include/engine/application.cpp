#include "application.h"
using namespace DT;

Vector2 Application::resolution = Vector2(500, 500);
sf::View Application::view = sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y));
sf::RenderWindow Application::renderWindow(sf::VideoMode(resolution.x, resolution.y), "Flappy Duck", sf::Style::Default);

void Application::SetResolution(Vector2 _res)
{
	resolution = _res;
	renderWindow.setSize(sf::Vector2u(resolution.x, resolution.y));
    view.setSize(resolution.x, resolution.y);
}

void Application::Initialize()
{
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);
    renderWindow.setView(view);
    renderWindow.setKeyRepeatEnabled(false);
    SetResolution(ProjectSettings::resolution);
}

bool Application::IsOpen()
{
    return renderWindow.isOpen();
}