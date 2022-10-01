# Contributing

If you are interested in contributing to this game engine, feel free to fork the repository and make your own changes.

**Note**: Please do not submit pull requests with new features or major changes. Instead, please file an issue first for discussion. If you'd like a feature implemented into the Game Engine, feel free to use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=feature_request.md&title=). Or if you encountered a bug, you may use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=bug_report.md&title=) instead.

## Setting up Ducktape for development

Before you proceed further, feel free to join [the Ducktape Discord Server](https://dsc.gg/ducktape) for any help that you may need!

### Clone the repository
Fork this repository to your own account.
Then, clone the repository using:
```
git clone https://github.com/<username>/Ducktape.git
```

### Install dependencies (Linux)
```sh
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
```

### Compile Ducktape
Execute the build script (`Build.bat` if you're on Windows, `Build.sh` if you're on Linux):
```
cd Ducktape
build
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
Enter the path to your C++ compiler (or the compiler command name if it's in your environment PATH variable):

Like, `g++` if you have the GNU compiler installed.
```
Specify your compiler:
(You may enter a path to your compiler or just the compiler's command name if th
e compiler path is already in your PATH environment variable)
```
Select the build type:
```
Choose the build type:
1) Debug
2) Release
Enter your option (1,2):
```

Then run 
```
./Editor/Editor.exe
```

### Commit naming in Ducktape follows a specific format:
```
[tag]: <Commit details>
```
where `[tag]` is:
- **feat** - a new feature is introduced with the changes
- **fix** - a bug fix has occured
- **chore** - changes that do not relate to a fix or feature and don't modify src or test files (for example updating dependencies)
- **refactor** - refactored code that neither fixes a bug nor adds a feature
- **docs** - updates to documentation such as the README or other markdown files
- **style** - changes that do not affect the meaning of the code, likely related to code formatting such as white-space, missing semi-colons, and so on
- **test** - including new or correcting previous tests
- **perf** - performance improvements
- **ci** - continuous integration related
- **build** - changes that affect the build system or external dependencies
- **revert** - reverts a previous commit

For example:
```
feat: Added Linux support
```
