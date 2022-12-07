#include "pyramid.h"
#include "pyramid_buffer.hpp"

Pyramid::Pyramid() {
	PyramidBuffer buffer;
	m_Buffer = new Buffer(buffer);
}

void Pyramid::Render()
{
	m_Buffer->Render();
}
