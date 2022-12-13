#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../../shader.hpp"
#include "../vertex.hpp"
#include "../texture.hpp"

namespace Core {
    class Mesh {
    public:
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Render(Shader& shader);
    private:
        unsigned int VAO, VBO, EBO;

        void SetupMesh();
    };
}