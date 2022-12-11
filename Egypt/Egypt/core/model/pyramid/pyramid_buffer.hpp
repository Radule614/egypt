#pragma once

#include "../buffer/ibufferable.hpp"
#include <vector>

class PyramidBuffer : public IBufferable {
public:
    PyramidBuffer();

    virtual std::vector<Vertex> GetVertices();
    virtual unsigned GetVertexCount();

private:
    static std::vector<Vertex> m_Vertices;
};