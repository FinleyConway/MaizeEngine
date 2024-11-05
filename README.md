# MaizeEngine

A small game engine made in c++.

## Building

1. Install Git and CMake.
2. Clone this repository: `git clone https://github.com/FinleyConway/MaizeEngine.git`.
3. If you use Linux, install SFML's dependencies using your system package manager. Debian-based distributions can use the following commands:
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```
4. Using CMake from the command line; making sure you are in the root directory of the project, use the following commands:
```
cmake -B build\
    -DMAIZE_SANDBOX=OFF\   #build sandbox 
    -DMAIZE_UNIT_TESTS=OFF #build unit-tests
cmake --build build
```

## License
MaizeEngine is under the [MIT license](https://github.com/FinleyConway/MaizeEngine/blob/master/LICENSE).

## External libraries used by MaizeEngine
- [SFML](https://github.com/SFML/SFML) is under the [zLib license](https://github.com/SFML/SFML/blob/master/license.md).
- [flecs](https://github.com/SanderMertens/flecs) is under the [MIT license](https://github.com/SanderMertens/flecs/blob/master/LICENSE).
- [Catch2](https://github.com/catchorg/Catch2/tree/devel) is under the [BSL-1.0 license](https://github.com/catchorg/Catch2/blob/devel/LICENSE.txt).