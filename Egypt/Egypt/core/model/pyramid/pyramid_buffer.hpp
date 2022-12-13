#pragma once

#include "../buffer/ibufferable.hpp"
#include <vector>

namespace Core {

    class PyramidBuffer : public IBufferable {
    public:
        PyramidBuffer();

        virtual std::vector<Core::Vertex> GetVertices();
        virtual unsigned GetVertexCount();

    private:
        static std::vector<Core::Vertex> m_Vertices;
    };

}