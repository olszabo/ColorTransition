#ifndef HEADERS_HPP
#define HEADERS_HPP

#pragma once
// C:/GitHub/Minecraft/textures/dirt.bmp

#include <Windows.h>  // Self explanatory
#include <vector>  // No explanation needed
#include <gdiplus.h>  // Displaying Images, will be useful for GUI
#include <cmath>  // Math operations like sin, cos
#include <iostream>  // Mostly just debugging - displaying errors
#include <iomanip>  // Set precision for displaying floats
#include <chrono>  // Real time for FPS couting
#include <map> // For holding textures
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>

#define WIN32_LEAN_AND_MEAN
using namespace Gdiplus;

#include "structs.hpp"
#include "functions.hpp"

extern int screenWidth;
extern int screenHeight;
extern int mouseX;
extern int mouseY;
extern bool keys[256];
extern controls ctrl;

extern float centerX;
extern float centerY;
extern vector2d screenCenter;

extern globals gl;

#endif // HEADERS_HPP