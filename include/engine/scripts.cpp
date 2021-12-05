#include "scripts.h"
using namespace DT;

BaseScript::BaseScript()
{
	ComponentExecutionHandler::baseScript.push_back(this);
}

RenderScript::RenderScript()
{
	ComponentExecutionHandler::renderScript.push_back(this);
}

PhysicsScript::PhysicsScript()
{
	ComponentExecutionHandler::physicsScript.push_back(this);
}

AudioScript::AudioScript()
{
	ComponentExecutionHandler::audioScript.push_back(this);
}

GameScript::GameScript()
{
	ComponentExecutionHandler::gameScript.push_back(this);
}