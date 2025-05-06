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
The executable appears in `build/win_64_build/src/app/Debug`, presumably
owing to the `src/app/CMakeLists.txt` defining the executable.

Having the .vscode/c_cpp_properties.json is what allows IntelliSense
to recognize the Qt library.

There exists a separate, command-line version that can be made, configuring with
```
cmake -S src/cmd build/cmd_version
```
and building with
```
cmake --build build/cmd_version
```