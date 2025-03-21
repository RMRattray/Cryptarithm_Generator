# Building

Building on Robert's machine requires two steps:  configuring and building.
Configuring is performed by the command:
```
cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.7.2.\msvc2022_64 -B build
```
and building by the command:
```
cmake --build build
```
run in the root directory of the project.

The source code is found in the 'src' folder.  The project is built
in a folder called "build" if using the commands above; more
elaborate build scripts can produce build folders with specific names.

Having the .vscode/c_cpp_properties.json is what allows IntelliSense
to recognize the Qt library.