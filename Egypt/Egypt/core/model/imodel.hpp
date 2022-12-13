#pragma once
#include "../shader.hpp"
#include "buffer/buffer.hpp"

namespace Core {

	class IModel {
	protected:
		Buffer* m_Buffer;
	public:
		virtual void Render(Shader& shader) = 0;

		void SetPosition(glm::vec3& pos);
		void SetRotation(glm::vec3& rotationAxis, float angle);
		void SetScale(glm::vec3& scale);

		void SetModelMatrix(glm::mat4& mat);
		void SetModelMatrix(glm::vec3& pos, glm::vec3 scale, glm::vec3 rotation, float angle);
	};

}
