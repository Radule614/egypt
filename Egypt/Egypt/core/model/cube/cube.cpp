#include "cube.hpp"
#include "cubebuffer.hpp"

Core::Cube::Cube() {
    CubeBuffer CubeBuffer;
    m_Buffer = new Buffer(CubeBuffer);
}

void
Core::Cube::Render(Shader& shader) {
    m_Buffer->Render(shader);
}