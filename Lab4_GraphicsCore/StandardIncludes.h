//Ramnooj
#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H
#define SDL_MAIN_HANDLED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <map>
#include <memory>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
        if (!(_cond)) { OutputDebugStringA(_msg); std::cerr << _msg << std::endl; std::abort(); }
#define GetCurrentDir _getcwd
typedef unsigned char byte;
#else
#include <unistd.h>
#define M_ASSERT(_cond, _msg) \
        if (!(_cond)) { std::cerr << _msg << std::endl; std::abort(); }
#define GetCurrentDir getcwd
typedef unsigned char byte;
#endif
using namespace std;
#include "Singleton.h"
#include "BasicStructs.h"

#endif // STANDARD_INCLUDES_H
