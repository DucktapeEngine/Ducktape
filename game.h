#pragma once

#include "bits/stdc++.h"
#include "./ducktape.h"
using namespace DT;

std::vector<GameObject*> gameObjects;

void ExampleScene(sf::RenderWindow& screen)
{
	gameObjects.clear();
	int n = -1;
	gameObjects.push_back(new GameObject("Name"));
	n++;
	gameObjects[n]->AddComponent(new Transform(Vector2(0.0,0.0), 0.0));
	gameObjects[n]->AddComponent(new SpriteRenderer("./Assets/Characters/character_0000.png"));
}