
# Contributing

**Note**: Please do not submit pull requests with new features or major changes. Instead, please file an issue first for discussion. If you'd like a feature implemented into the Game Engine, feel free to use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=feature_request.md&title=). Or if you encountered a bug, you may use [this issue template](https://github.com/DucktapeEngine/Ducktape/issues/new?assignees=&labels=&template=bug_report.md&title=) instead.

### How to start contributing:

If you'd like to work on a specific [Issue](https://github.com/DucktapeEngine/Ducktape/issues), please post a comment stating that you are interested in working on it. After a maintainer confirms/assigns you the issue, you may start working on it.

### Cloning the repository
Use the command:
```git clone --single-branch --branch development https://github.com/DucktapeEngine/Ducktape.git```
In order to clone the `development` branch of the repository in your local directory.

### Compiling Ducktape
You may compile one of the examples (as of the time of writing, there's only one, [a Flappy Bird clone made in Ducktape](https://github.com/DucktapeEngine/Ducktape/blob/development/examples/flappybird.cpp) using:

Open terminal in the root directory.
```
mkdir build
cd build
cmake ..
make
```
and
```
./ducktape
```
to run the example program.

After working on the project, please create a pull request - which the maintainers would review and suggest improvements/merge the pull request. 
If you'd like any kind of help on Ducktape, feel free to join [Ducktape's Official Discord server](https://ducktapeengine.github.io/discord) and ask for help.

That's it.

Good luck! :)
