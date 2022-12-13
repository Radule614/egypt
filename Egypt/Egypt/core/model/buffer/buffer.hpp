#pragma once

#include <GL/glew.h>
#include <iostream>
#include "ibufferable.hpp"
#include <glm/glm.hpp>
#include "../../shader.hpp"
#include "../texture.hpp"
#include <glm/ext/matrix_transform.hpp>

#define POSITION_LOCATION 0
#define NORMAL_LOCATION 1
#define TEXCOORD_LOCATION 2
#define TANGENT_LOCATION 3

namespace Core {

	class Buffer {
	private:
		unsigned m_VAO;
		unsigned m_VBO;
		unsigned m_EBO;
		unsigned m_IndexCount;
		unsigned m_VertexCount;

		std::vector<Texture> m_Textures;
		glm::mat4 m_ModelMatrix;

		void LoadTexture(std::string& path, std::string type);
		void BindTextures(Shader& shader);
	public:
		Buffer(IBufferable& bufferable);
		void AddDiffuseMap(std::string path);
		void AddSpecularMap(std::string path);
		void AddNormalMap(std::string path);
		void Render(Shader& shader);

		void SetPosition(glm::vec3& pos);
		void SetRotation(glm::vec3& rotationAxis, float angle);
		void SetScale(glm::vec3& scale);

		void SetModelMatrix(glm::mat4& mat);
		void SetModelMatrix(glm::vec3& pos, glm::vec3 scale, glm::vec3 rotation, float angle);
	};

}