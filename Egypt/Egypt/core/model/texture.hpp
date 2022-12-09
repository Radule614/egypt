#pragma once

#include <string>
#include <GL/glew.h>
#include "stb_image.hpp"
#include <iostream>

unsigned int LoadTextureFromFile(const std::string& path, const std::string& directory);
