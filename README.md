
<br><br><br>
<p align="center">
    <a href="https://ducktapeengine.github.io/" target="_blank">
        <img src="https://raw.githubusercontent.com/DucktapeEngine/Branding/main/banner-transparent.png" alt="logo" width="600px"/>
    </a>
<p/>
<h1 align="center">Convenience, that's Ducktape.</h1>

<p align="center">
    <a href="https://github.com/ducktapeengine/ducktape/blob/master/LICENSE" target="blank">
    <img src="https://img.shields.io/github/license/ducktapeengine/ducktape?style=for-the-badge" alt="Ducktape license" />
    </a>
    <a href="https://dsc.gg/ducktape" target="blank">
    <img src="https://img.shields.io/discord/831047342215659521?style=for-the-badge" alt="Ducktape Discord" />
    </a>
    <a href="https://github.com/ducktapeengine/ducktape/fork" target="blank">
    <img src="https://img.shields.io/github/forks/ducktapeengine/ducktape?style=for-the-badge" alt="Ducktape forks"/>
    </a>
    <a href="https://github.com/ducktapeengine/ducktape/stargazers" target="blank">
    <img src="https://img.shields.io/github/stars/ducktapeengine/ducktape?style=for-the-badge" alt="Ducktape stars"/>
    </a>
    <a href="https://github.com/ducktapeengine/ducktape/issues" target="blank">
    <img src="https://img.shields.io/github/issues/ducktapeengine/ducktape?style=for-the-badge" alt="Ducktape issues"/>
    </a>
    <a href="https://github.com/ducktapeengine/ducktape/pulls" target="blank">
    <img src="https://img.shields.io/github/issues-pr/ducktapeengine/ducktape?style=for-the-badge" alt="Ducktape pull-requests"/>
    </a>
</p>

<p align="center">
    <a href="https://ducktapeengine.github.io/demo" target="blank">View Demos</a>
    ·
    <a href="https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=bug_report.md&title=">Report Bug</a>
    ·
    <a href="https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=feature_request.md&title=">Request Feature</a>
</p>

# 👋 Introducing `Ducktape`
`Ducktape` is an open source 2d game engine that gives users an easy-to-use library to develop games for platforms including Windows and Linux (more platforms coming soon™️!) It has an integrated Scripting, Rendering, Audio, Physics engine which you can use to make your game stand out.

   
### If you like this project, consider being one of many people who has supported this project with stars ⭐!

[![Stargazers repo roster for @Ducktapeengine/Ducktape](https://reporoster.com/stars/Ducktapeengine/Ducktape)](https://github.com/Ducktapeengine/ducktape/stargazers)
    
# ✨ Features

⚙️ **Scene-Entity-Component system**
- Create Scenes, Entities, Components in a tree-based system
- Scriptable components
- 
🖼️ **Rendering engine**
- Render sprites from .bmp, .png, .tga and .jpg image formats.
- Frame by frame animation controller (Coming soon).

🔊 **Audio engine**
- Play sound/music from audio formats including .wav, .ogg and .flac with the ability to pause/stop/set seek the song.
- Many customization options including loop, pitch, volume, spatial distance.

⚛️ **Physics engine**
- A fully fledged physics engine with support for Rigidbodies.
- Box/Circle/Polygon/Edge colliders.
- Distance/Friction/Hinge joints.
- Raycasts and OnCollisionEnter handlers.
    
# Get Started
Interested in using the library? We have a [manual](https://ducktapeengine.github.io/docs/intro) for how things work in Ducktape and how to use the library to create your own first game.
    
# 🖥️ How to set up `Ducktape` for development?
You can compile and run Ducktape locally with a few easy steps.  
Clone the repository using git:
```
git clone https://github.com/DucktapeEngine/Ducktape.git
```
Execute the build script (`build.bat` if you're on Windows, `build.sh` if you're on Linux):
```
cd Ducktape
./build.bat
```
Select the generator for CMake
```
Setting up Ducktape for compiling...
Choose your generator:
1) Borland Makefiles
2) MSYS Makefiles
3) MinGW Makefiles (Default for Windows)
4) NMake Makefiles
5) NMake Makefiles JOM
6) Unix Makefiles (Default for Linux)
7) Watcom WMake
Enter your option (1,2,3,4,5,6,7):
```
Enter the path to your compiler (or the compiler command name if it's in your environment PATH variable):
```
Specify your compiler:
(You may enter a path to your compiler or just the compiler's command name if th
e compiler path is already in your PATH environment variable)
```
# 🔨 Built with:
- [Box2D](https://github.com/erincatto/box2d) - a 2D physics engine for games
- [SFML](https://github.com/SFML/SFML) - a Simple and Fast Multimedia Library
    
# License
This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

# 🤝 Contributing to `Ducktape`
All contributions are welcome! Please help us to grow by contributing to the project.

If you wish to contribute, you can work on any features/bugs [listed here](https://github.com/DucktapeEngine/Ducktape/issues) or create one on your own. After adding your code, please send us a Pull Request.`+

> Please read [`CONTRIBUTING`](CONTRIBUTING.md) for details on our [`CODE OF CONDUCT`](CODE_OF_CONDUCT.md), and the process for submitting pull requests to us.

# 🫂 Support
This project is relatively new to the open source community, and we hope to make a difference! So if you like this project, please consider supporting us by simply starring the repository! It really helps.