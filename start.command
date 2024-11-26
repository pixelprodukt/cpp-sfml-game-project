#!/bin/bash

# Go to build folder
cd build

# compile main.cpp
/usr/bin/clang++ -DSFML_STATIC -I/Users/adriansemmler/Documents/coding/cpp-sfml-game-project/include -isystem /Users/adriansemmler/Documents/coding/cpp-sfml-game-project/build/_deps/sfml-src/include -g -std=gnu++17 -arch arm64 -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk -mmacosx-version-min=14.7 -F/Users/adriansemmler/Documents/coding/cpp-sfml-game-project/build/_deps/sfml-src/extlibs/libs-osx/Frameworks  -o CMakeFiles/main.dir/src/main.cpp.o -c /Users/adriansemmler/Documents/coding/cpp-sfml-game-project/src/main.cpp

# run make to build project
make

# go to bin folder
cd bin

# run main file
./main