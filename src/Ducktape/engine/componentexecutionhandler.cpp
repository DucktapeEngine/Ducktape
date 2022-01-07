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

#include <Ducktape/engine/componentexecutionhandler.h>
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

void ComponentExecutionHandler::OnApplicationClose()
{
	for(int i=0;i<baseScript.size();i++){baseScript[i]->OnApplicationClose();}
	for(int i=0;i<physicsScript.size();i++){physicsScript[i]->OnApplicationClose();}
	for(int i=0;i<audioScript.size();i++){audioScript[i]->OnApplicationClose();}
	for(int i=0;i<gameScript.size();i++){gameScript[i]->OnApplicationClose();}
	for(int i=0;i<renderScript.size();i++){renderScript[i]->OnApplicationClose();}
}