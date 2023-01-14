#pragma once
#include <glm/glm.hpp>

namespace Core {

	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

	struct PointLight {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;

		PointLight(glm::vec3 pos, glm::vec3 color) {
			position = pos;
			ambient = color;
			diffuse = color;
			specular = color;
			constant = 0.005f;
			linear = 0.005f;
			quadratic = 0.02f;
		}

		PointLight(glm::vec3 pos, glm::vec3 a, glm::vec3 d, glm::vec3 s, float x, float y, float z) {
			position = pos;
			ambient = a;
			diffuse = d;
			specular = s;
			constant = x;
			linear = y;
			quadratic = z;
		}
	};

	struct DirectionalLight {
		glm::vec3 direction;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct SpotLight {
		glm::vec3 direction;
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float cutOff;
		float outerCutOff;
		float constant;
		float linear;
		float quadratic;

		SpotLight(glm::vec3 pos, glm::vec3 dir) {
			position = pos;
			direction = dir;
			ambient = glm::vec3(0.0f);
			diffuse = glm::vec3(0.6f, 0.0f, 0.0f);
			specular = glm::vec3(1.0f, 0.0f, 0.0f);
			cutOff = glm::cos(glm::radians(6.0f));
			outerCutOff = glm::cos(glm::radians(9.0f));
			constant = 0;
			linear = 0.009f;
			quadratic = 0;
		}
	};
}
