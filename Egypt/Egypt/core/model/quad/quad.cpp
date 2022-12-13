#include "quad.hpp"

Core::Quad::Quad()
{
	QuadBuffer buffer;
	m_Buffer = new Buffer(buffer);
	m_Buffer->AddDiffuseMap("assets/sand/sand.jpg");
	m_Buffer->AddSpecularMap("assets/sand/specular.jpg");
	m_Buffer->AddNormalMap("assets/sand/normal.jpg");
}

void Core::Quad::Render(Shader& shader)
{
	m_Buffer->Render(shader);
}
