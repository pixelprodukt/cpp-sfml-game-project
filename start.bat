@echo off
REM Navigate to the build folder
cd "./build"

REM Compile main.cpp
echo Compiling...
C:\msys64\ucrt64\bin\g++.exe -DSFML_STATIC @CMakeFiles/main.dir/includes_CXX.rsp -g -o CMakeFiles\main.dir\src\main.cpp.obj -c C:\Users\ase\Documents\cpp\cpp-sfml-game-project\src\main.cpp

REM Execute the second command
echo Building project...
mingw32-make

REM Change to bin folder
cd "./bin"

REM Run the main.exe file
echo Running main.exe...
main.exe

echo Script execution completed.
pause