// /*
// MIT License

// Copyright (c) 2022 Ducktape

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// */

// #include <Input/Input.h>

// namespace Ducktape
// {
//     void Input::Init()
//     {
//         glfwSetKeyCallback(Window::window, KeyCallback);
//     }

//     void Input::Tick()
//     {
//         keyPressedMap.clear();
//         keyReleasedMap.clear();

//         mousePressedMap.clear();
//         mouseReleasedMap.clear();

//         double xpos, ypos;
//         glfwGetCursorPos(Window::window, &xpos, &ypos);
//         mousePosition = glm::vec2(xpos, ypos);
//     }

//     void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
//     {
//         if (action == GLFW_PRESS)
//         {
//             keyHeldMap[static_cast<Key>(key)] = true;
//             keyPressedMap[static_cast<Key>(key)] = true;
//         }
//         else if (action == GLFW_RELEASE)
//         {
//             keyHeldMap[static_cast<Key>(key)] = false;
//             keyReleasedMap[static_cast<Key>(key)] = true;
//         }
//     }

//     bool Input::KeyHeld(Key key)
//     {
//         return keyHeldMap[key];
//     }

//     bool Input::KeyPressed(Key key)
//     {
//         return keyPressedMap[key];
//     }

//     bool Input::KeyReleased(Key key)
//     {
//         return keyReleasedMap[key];
//     }

//     void Input::SetMouseMode(MouseMode mode)
//     {
//         glfwSetInputMode(Window::window, GLFW_CURSOR, mode);
//     }

//     void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
//     {
//         if (action == GLFW_PRESS)
//         {
//             mouseHeldMap[button] = true;
//             mousePressedMap[button] = true;
//         }
//         else if (action == GLFW_RELEASE)
//         {
//             mouseHeldMap[button] = false;
//             mouseReleasedMap[button] = true;
//         }
//     }

//     bool Input::MouseHeld(int button)
//     {
//         return mouseHeldMap[button];
//     }

//     bool Input::MousePressed(int button)
//     {
//         return mousePressedMap[button];
//     }

//     bool Input::MouseReleased(int button)
//     {
//         return mouseReleasedMap[button];
//     }

//     void Input::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
//     {
//         scrollDelta.x = xoffset;
//         scrollDelta.y = yoffset;
//     }

//     bool Input::JoystickConnected(int joystick)
//     {
//         return glfwJoystickPresent(joystick);
//     }

//     std::vector<float> Input::JoystickAxes(int joystick)
//     {
//         int count;
//         const float *axes = glfwGetJoystickAxes(joystick, &count);
//         std::vector<float> axesVector(axes, axes + count);
//         return axesVector;
//     }

//     std::vector<unsigned char> Input::JoystickButtons(int joystick)
//     {
//         int count;
//         const unsigned char *buttons = glfwGetJoystickButtons(joystick, &count);
//         std::vector<unsigned char> buttonsVector(buttons, buttons + count);
//         return buttonsVector;
//     }

//     std::string Input::GetClipboard()
//     {
//         return glfwGetClipboardString(Window::window);
//     }

//     void Input::SetClipboard(std::string string)
//     {
//         glfwSetClipboardString(Window::window, string.c_str());
//     }
// }