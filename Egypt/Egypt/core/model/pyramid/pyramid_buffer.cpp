#include "pyramid_buffer.hpp"

std::vector<Vertex> PyramidBuffer::m_Vertices = {
    Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(6.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(6.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},

    Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(-0.6f, 0.5f, 0.0f), glm::vec2(6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(-0.6f, 0.5f, 0.0f), glm::vec2(3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.6f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},

    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.6f), glm::vec2(6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(0.0f, 0.5f, -0.6f), glm::vec2(3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.6f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},

    Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.6f, 0.5f, 0.0f), glm::vec2(6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(0.6f, 0.5f, 0.0f), glm::vec2(3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.6f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},

    Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.5f, 0.6f), glm::vec2(6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(0.0f, 0.5f, 0.6f), glm::vec2(3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.5f, 0.6f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
};

PyramidBuffer::PyramidBuffer() {
    CalculateTangent(m_Vertices);
}

std::vector<Vertex> PyramidBuffer::GetVertices()
{
    return m_Vertices;
}

unsigned PyramidBuffer::GetVertexCount()
{
    return m_Vertices.size();
}