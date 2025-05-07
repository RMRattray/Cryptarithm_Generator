# Building

Building on Robert's machine requires two steps:  configuring and building.
Configuring is performed by the command:
```
cmake -B build/win_64_build
```
and building by the command:
```
cmake --build build/win_64_build
```
run in the root directory of the project.

The project is built
in a folder called `build/win_64_build` if using the commands above; more
elaborate build scripts can produce build folders with specific names.
The executable appears as `build/win_64_build/src/app/Debug/cryptarithm.exe`.
It should look roughly like this:

![Screenshot of v0.1](https://github.com/user-attachments/assets/4bb3acf9-0e1d-4697-a461-d44a4b300353)

There exists a separate, command-line version that can be made, configuring with
```
cmake -S src/cmd -B build/cmd_version
```
and building with
```
cmake --build build/cmd_version
```
