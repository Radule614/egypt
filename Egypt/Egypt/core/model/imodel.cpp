#include "imodel.hpp"

void Core::IModel::SetPosition(glm::vec3& pos)
{
	m_Buffer->SetPosition(pos);
}

void Core::IModel::SetRotation(glm::vec3& rotationAxis, float angle)
{
	m_Buffer->SetRotation(rotationAxis, angle);
}

void Core::IModel::SetScale(glm::vec3& scale)
{
	m_Buffer->SetScale(scale);
}

void Core::IModel::SetModelMatrix(glm::mat4& mat)
{
	m_Buffer->SetModelMatrix(mat);
}

void Core::IModel::SetModelMatrix(glm::vec3& pos, glm::vec3 scale, glm::vec3 rotation, float angle)
{
	m_Buffer->SetModelMatrix(pos, scale, rotation, angle);
}
