#include "quad_buffer.hpp"

std::vector<float> QuadBuffer::m_Vertices = {
    //      POS      |     NORMALS     |  TexCoords
    // X    Y     Z     X     Y     Z     X     Y

    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};

float* QuadBuffer::GetVertices()
{
    return m_Vertices.data();
}

unsigned QuadBuffer::GetVertexCount()
{
    return m_Vertices.size();
}

unsigned QuadBuffer::GetVertexElementCount()
{
    return 8;
}
