#pragma once

#include <vector>
#include "../buffer/ibufferable.hpp"

class CubeBuffer : public IBufferable {
public:
    CubeBuffer();
private:
    static std::vector<Vertex> m_Vertices;

    virtual std::vector<Vertex> GetVertices();
    virtual unsigned GetVertexCount();
};