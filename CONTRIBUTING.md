

# Contributing

**Note**: Please do not submit pull requests with new features or major changes. Instead, please file an issue first for discussion. If you'd like a feature implemented into the Game Engine, feel free to use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=feature_request.md&title=). Or if you encountered a bug, you may use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=bug_report.md&title=) instead.

## 🖥️ How to set up `Ducktape` for development?
You can compile Ducktape locally with a few easy steps.  
Clone the repository using git:
```
git clone https://github.com/DucktapeEngine/Ducktape.git
```
Execute the build script (`build.bat` if you're on Windows, `build.sh` if you're on Linux):
```
cd Ducktape
build.bat
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

## Code practices
We try our best to follow [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html) for maximum consistency, and we hope you do too.
