#ifndef COMPONENTEXECUTIONHANDLER_H
#define COMPONENTEXECUTIONHANDLER_H

#include <vector>
#include "behaviourscript.h"

namespace DT
{
	namespace ComponentExecutionHandler 
	{
		extern std::vector<BehaviourScript*> baseScript;
		extern std::vector<BehaviourScript*> renderScript;
		extern std::vector<BehaviourScript*> physicsScript;
		extern std::vector<BehaviourScript*> audioScript;
		extern std::vector<BehaviourScript*> gameScript;

		void Start();
		void Update();
		void FixedUpdate();
	}
}

#endif