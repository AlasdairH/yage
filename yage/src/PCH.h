#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC

#define SHADER_BINDPOINT_CAMERA_VP 0

// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>   
#include <sstream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <array>
#include <unordered_map>

// External
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// Program
#include "CompileSettings.h"
#include "Log.h"
#include "GraphicsContext_OpenGL.h"
#include "Timer.h"