# Contributing

If you are interested in contributing to this game engine, feel free to fork the repository and make your own changes.

**Note**: Please do not submit pull requests with entirely new features or major changes. Instead, please file an issue first for discussion. If you'd like a feature implemented into the engine, feel free to use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=feature_request.md&title=) to discuss it beforehand. Or if you encountered a bug, you may use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=bug_report.md&title=) instead.

## Setting up Ducktape for development

Before you proceed further, feel free to join [the Ducktape Discord Server](https://dsc.gg/ducktape) for any help regarding Ducktape.

### Clone the repository
Fork this repository to your own account.
Then, clone the repository using:
```
git clone https://github.com/<username>/Ducktape.git
```

### Install dependencies (For Linux users)
#### Debian

```sh
chmod +x install-deps-debian.sh
sudo ./install-deps-debian.sh
```
or
```sh
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libglfw3-dev libassimp-dev
```
#### Arch

```sh
chmod +x install-deps-arch.sh
sudo ./install-deps-arch.sh
```
or
```sh
sudo pacman -S libx11 libxrandr libxinerama libxcursor libxi mesa assimp glfw-x11
```

### Compile Ducktape
```bat
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./Build
cd Build
cmake --build .
```
Now run 
```
./DucktapeRuntime.exe
```

### Ducktape's commit message convention:
```
<tag>: <commit msg>
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
feat: added audio system
```
