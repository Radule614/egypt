#pragma once

#include "../buffer/ibufferable.hpp"
#include <vector>

class QuadBuffer : public IBufferable {
public:
    virtual float* GetVertices();
    virtual unsigned GetVertexCount();
    virtual unsigned GetVertexElementCount();

private:
    static std::vector<float> m_Vertices;
};