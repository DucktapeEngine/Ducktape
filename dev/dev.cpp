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

// A little playground for new on-development features and stuff for contributors and developers.
// Feel free to edit this as you like.

#include <Ducktape/ducktape.h>
using namespace DT;

#include <string>

const std::string ASSETPATH = "../dev/assets/"; // Relative path from build directory

class FollowMouse : public BehaviourScript {
public:
    void Tick() {
        // Get the mouse position
        Vector2 mousePos = Camera::ScreenToWorldPos(Input::GetMousePosition());
        entity->transform->SetPosition(mousePos);
    }
};

class SampleScene : public Scene {
    void Init()
    {
        Entity::Instantiate("Camera", Vector2(15.f, 0.f), 0.f, Vector2(1.f, 1.f))->AddComponent<Camera>();
        Entity::Instantiate("Player", Vector2(0, 0), 0.f, Vector2(1.f, 1.f))
        ->AddComponent<FollowMouse>()->entity
        ->AddComponent<SpriteRenderer>()
        ->SetSpritePath(ASSETPATH + "block.png")
        ->SetPixelPerUnit(10);
    }
};

int main()
{
    ProjectSettings::SceneManagement::initialScene = new SampleScene();
    ProjectSettings::Application::resizable = false;
    DT::Init();
}