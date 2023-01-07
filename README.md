# SDL2snake

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ac6a0bb578ff4bf3b6de9f9013ec8b1d)](https://app.codacy.com/gh/Joker2770/SDL2snake?utm_source=github.com&utm_medium=referral&utm_content=Joker2770/SDL2snake&utm_campaign=Badge_Grade_Settings)
[![sdl2snake](https://snapcraft.io/sdl2snake/badge.svg)](https://snapcraft.io/sdl2snake)

A game of snake made with SDL2. 

## Dependencies
Required:
* [cmake](http://www.cmake.org) - buildsystem
* g++ (>= 7.4.0 recommended)
* gcc (>= 7.4.0 recommended)
* libsdl2-dev,libsdl2-ttf-dev (Linux), sdl2.nuget,sdl2_ttf.nuget (Windows)

## Build on Ubuntu(Linux)
~~~
sudo apt install libsdl2-dev libsdl2-ttf-dev
git clone https://github.com/Joker2770/SDL2snake.git
cd SDL2snake
mkdir build
cd build
cmake ..
make
cp ../res/lazy.ttf ./
./SDL2snake
sudo make install
SDL2snake
~~~

## Build on Windows
~~~
git clone https://github.com/Joker2770/SDL2snake.git
cd SDL2snake/msvc/
~~~
Then double click 'SDL2snake.sln', build with Visual Studio.

