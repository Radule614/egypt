#pragma once

#include <vector>
#include "../buffer/ibufferable.hpp"
#include "../texture.hpp"

namespace Core {

    class QuadBuffer : public IBufferable {
    public:
        QuadBuffer();

        virtual std::vector<Vertex> GetVertices();
        virtual unsigned GetVertexCount();

    private:
        static std::vector<Vertex> m_Vertices;
    };

}
