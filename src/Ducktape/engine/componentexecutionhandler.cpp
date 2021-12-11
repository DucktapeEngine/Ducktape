#include "componentexecutionhandler.h"
using namespace DT;

std::vector<BehaviourScript*> ComponentExecutionHandler::baseScript;
std::vector<BehaviourScript*> ComponentExecutionHandler::renderScript;
std::vector<BehaviourScript*> ComponentExecutionHandler::physicsScript;
std::vector<BehaviourScript*> ComponentExecutionHandler::audioScript;
std::vector<BehaviourScript*> ComponentExecutionHandler::gameScript;

void ComponentExecutionHandler::Start()
{
	for(int i=0;i<baseScript.size();i++){baseScript[i]->Start();}
	for(int i=0;i<physicsScript.size();i++){physicsScript[i]->Start();}
	for(int i=0;i<audioScript.size();i++){audioScript[i]->Start();}
	for(int i=0;i<renderScript.size();i++){renderScript[i]->Start();}
	for(int i=0;i<gameScript.size();i++){gameScript[i]->Start();}
}

void ComponentExecutionHandler::Update()
{
	for(int i=0;i<baseScript.size();i++){baseScript[i]->Update();}
	for(int i=0;i<physicsScript.size();i++){physicsScript[i]->Update();}
	for(int i=0;i<audioScript.size();i++){audioScript[i]->Update();}
	for(int i=0;i<gameScript.size();i++){gameScript[i]->Update();}
	for(int i=0;i<renderScript.size();i++){renderScript[i]->Update();}
}

void ComponentExecutionHandler::FixedUpdate()
{
	for(int i=0;i<baseScript.size();i++){baseScript[i]->FixedUpdate();}
	for(int i=0;i<physicsScript.size();i++){physicsScript[i]->FixedUpdate();}
	for(int i=0;i<audioScript.size();i++){audioScript[i]->FixedUpdate();}
	for(int i=0;i<gameScript.size();i++){gameScript[i]->FixedUpdate();}
	for(int i=0;i<renderScript.size();i++){renderScript[i]->FixedUpdate();}
}

void ComponentExecutionHandler::OnApplicationClose()
{
	for(int i=0;i<baseScript.size();i++){baseScript[i]->OnApplicationClose();}
	for(int i=0;i<physicsScript.size();i++){physicsScript[i]->OnApplicationClose();}
	for(int i=0;i<audioScript.size();i++){audioScript[i]->OnApplicationClose();}
	for(int i=0;i<gameScript.size();i++){gameScript[i]->OnApplicationClose();}
	for(int i=0;i<renderScript.size();i++){renderScript[i]->OnApplicationClose();}
}