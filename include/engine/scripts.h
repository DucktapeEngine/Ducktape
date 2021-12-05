#ifndef SCRIPTS_H
#define SCRIPTS_H

#include "behaviourscript.h"
#include "componentexecutionhandler.h"

namespace DT
{
	class BaseScript : public BehaviourScript
	{
	public:
		BaseScript();
	};

	class RenderScript : public BehaviourScript
	{
	public:
		RenderScript();
	};

	class PhysicsScript : public BehaviourScript
	{
	public:
		PhysicsScript();
	};

	class AudioScript : public BehaviourScript
	{
	public:
		AudioScript();
	};

	class GameScript : public BehaviourScript
	{
	public:
		GameScript();
	};
}

#endif