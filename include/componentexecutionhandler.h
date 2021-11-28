#ifndef COMPONENTEXECUTIONHANDLER_H
#define COMPONENTEXECUTIONHANDLER_H

namespace ComponentExecutionHandler 
{
	std::vector<BehaviourScript*> baseScript;
	std::vector<BehaviourScript*> renderScript;
	std::vector<BehaviourScript*> physicsScript;
	std::vector<BehaviourScript*> audioScript;
	std::vector<BehaviourScript*> gameScript;

	void Start()
	{
		for(int i=0;i<baseScript.size();i++){baseScript[i]->Start();}
		for(int i=0;i<physicsScript.size();i++){physicsScript[i]->Start();}
		for(int i=0;i<audioScript.size();i++){audioScript[i]->Start();}
		for(int i=0;i<renderScript.size();i++){renderScript[i]->Start();}
		for(int i=0;i<gameScript.size();i++){gameScript[i]->Start();}
	}

	void Update()
	{
		for(int i=0;i<baseScript.size();i++){baseScript[i]->Update();}
		for(int i=0;i<physicsScript.size();i++){physicsScript[i]->Update();}
		for(int i=0;i<audioScript.size();i++){audioScript[i]->Update();}
		for(int i=0;i<gameScript.size();i++){gameScript[i]->Update();}
		for(int i=0;i<renderScript.size();i++){renderScript[i]->Update();}
	}

	void FixedUpdate()
	{
		for(int i=0;i<baseScript.size();i++){baseScript[i]->FixedUpdate();}
		for(int i=0;i<physicsScript.size();i++){physicsScript[i]->FixedUpdate();}
		for(int i=0;i<audioScript.size();i++){audioScript[i]->FixedUpdate();}
		for(int i=0;i<gameScript.size();i++){gameScript[i]->FixedUpdate();}
		for(int i=0;i<renderScript.size();i++){renderScript[i]->FixedUpdate();}
	}
}

class BaseScript : public BehaviourScript
{
public:
	BaseScript()
	{
		ComponentExecutionHandler::baseScript.push_back(this);
	}
};

class RenderScript : public BehaviourScript
{
public:
	RenderScript()
	{
		ComponentExecutionHandler::renderScript.push_back(this);
	}
};

class PhysicsScript : public BehaviourScript
{
public:
	PhysicsScript()
	{
		ComponentExecutionHandler::physicsScript.push_back(this);
	}
};

class AudioScript : public BehaviourScript
{
public:
	AudioScript()
	{
		ComponentExecutionHandler::audioScript.push_back(this);
	}
};

class GameScript : public BehaviourScript
{
public:
	GameScript()
	{
		ComponentExecutionHandler::gameScript.push_back(this);
	}
};

#endif