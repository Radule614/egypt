#include "pyramid_buffer.hpp"

std::vector<float> PyramidBuffer::m_Vertices = {
    //      POS        |     NORMALS   
    // X    Y      Z      X     Y     Z

    -0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,  0.0f, -1.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,0.0f, -1.0f, 0.0f,

    -0.5f, 0.0f, 0.5f, -0.6f, 0.5f, 0.0f,
    0.0f, 0.6f, 0.0f, -0.6f, 0.5f, 0.0f,
    -0.5f, 0.0f, -0.5f, -0.6f, 0.5f, 0.0f,

    -0.5f, 0.0f, -0.5f, 0.0f, 0.5f, -0.6f,
    0.0f, 0.6f, 0.0f, 0.0f, 0.5f, -0.6f,
    0.5f, 0.0f, -0.5f, 0.0f, 0.5f, -0.6f,

    0.5f, 0.0f, -0.5f, 0.6f, 0.5f, 0.0f,
    0.0f, 0.6f, 0.0f, 0.6f, 0.5f, 0.f,
    0.5f, 0.0f, 0.5f, 0.6f, 0.5f, 0.0f,

    0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.6f,
    0.0f, 0.6f, 0.0f, 0.0f, 0.5f, 0.6f,
    -0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.6f,
};

float* PyramidBuffer::GetVertices()
{
    return m_Vertices.data();
}

unsigned PyramidBuffer::GetVertexCount()
{
    return m_Vertices.size();
}

unsigned PyramidBuffer::GetVertexElementCount()
{
    return 6;
}
