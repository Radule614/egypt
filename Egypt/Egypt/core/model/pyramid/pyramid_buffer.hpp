#pragma once

#include "../buffer/ibufferable.hpp"
#include <vector>

class PyramidBuffer : public IBufferable {
public:
    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();

private:
    static std::vector<float> m_Vertices;
};