#pragma once

#include <string>
#include <GL/glew.h>
#include "stb_image.hpp"
#include <iostream>

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

unsigned int LoadTextureFromFile(const std::string& path, const std::string& directory);
