#pragma once

#include "../buffer/ibufferable.hpp"
#include <vector>

#include "../texture.hpp"

class QuadBuffer : public IBufferable {
public:
    QuadBuffer();

    virtual std::vector<Vertex> GetVertices();
    virtual unsigned GetVertexCount();

private:
    static std::vector<Vertex> m_Vertices;
};