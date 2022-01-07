/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/engine/application.h>
using namespace DT;

Vector2 Application::Private::resolution = Vector2(500, 500);
sf::View Application::view = sf::View(sf::FloatRect(0.f, 0.f, Private::resolution.x, Private::resolution.y));
sf::RenderWindow Application::renderWindow(sf::VideoMode(Private::resolution.x, Private::resolution.y), "Flappy Duck", sf::Style::Default);

void Application::SetResolution(Vector2 _res)
{
	Private::resolution = _res;
	renderWindow.setSize(sf::Vector2u(Private::resolution.x, Private::resolution.y));
    view.setSize(Private::resolution.x, Private::resolution.y);
}

Vector2 Application::GetResolution()
{
    return Application::Private::resolution;
}

void Application::Initialize()
{
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);
    renderWindow.setView(view);
    renderWindow.setKeyRepeatEnabled(false);
    SetResolution(ProjectSettings::initialResolution);
}

bool Application::IsOpen()
{
    return renderWindow.isOpen();
}