#pragma once
#include <GL/glew.h>
#include <vector>

#include "../shader.hpp"
#include "../model/texture.hpp"

namespace Core {

	class Skybox {
	public:
		Skybox(Core::Shader& skyboxShader);
		void Render();
	private:
		Core::Shader& m_Shader;
		unsigned m_VAO;
		unsigned m_VBO;
		static std::vector<float> data;
		unsigned int m_CubemapTexture;

	};

}