#pragma once

#include <vector>
#include "../buffer/ibufferable.hpp"

namespace Core {
    class CubeBuffer : public IBufferable {
    public:
        CubeBuffer();
    private:
        static std::vector<Core::Vertex> m_Vertices;

        virtual std::vector<Core::Vertex> GetVertices();
        virtual unsigned GetVertexCount();
    };
}
