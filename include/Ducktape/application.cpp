#include <SFML/Window.hpp>
#include "application.hpp"
#include "debug.hpp"

void Application::Initialize()
{
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);
    renderWindow.setView(view);
}

bool Application::IsOpen()
{
    return renderWindow.isOpen();
}