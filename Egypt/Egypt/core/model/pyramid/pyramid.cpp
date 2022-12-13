#include "pyramid.hpp"

Core::Pyramid::Pyramid() {
	PyramidBuffer buffer;
	m_Buffer = new Buffer(buffer);
	m_Buffer->AddDiffuseMap("assets/brick/brick.jpg");
	m_Buffer->AddSpecularMap("assets/brick/specular.jpg");
	m_Buffer->AddNormalMap("assets/brick/normal.jpg");
}

void Core::Pyramid::Render(Shader& shader)
{
	m_Buffer->Render(shader);
}
