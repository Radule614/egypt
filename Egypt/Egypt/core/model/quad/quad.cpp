#include "quad.hpp"
#include "quad_buffer.hpp"

Quad::Quad()
{
	QuadBuffer buffer;
	m_Buffer = new Buffer(buffer);
}

void Quad::Render()
{
	m_Buffer->Render();
}
