#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../../utility/stb_image.hpp"

namespace Core {

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    static std::vector<Texture> LoadedTextures;

    unsigned int LoadTextureFromFile(const std::string& fullpath);
    unsigned int LoadTextureFromFile(const std::string& path, const std::string& directory);
    unsigned int LoadCubemap(std::vector<std::string> faces);
}