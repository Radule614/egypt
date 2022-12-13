#pragma once
#include <vector>
#include "../vertex.hpp"

namespace Core {

	class IBufferable {
	public:
		virtual std::vector<Core::Vertex> GetVertices() = 0;
		virtual unsigned* GetIndices() {
			return 0;
		};
		virtual unsigned GetVertexCount() = 0;
		virtual unsigned GetIndexCount() {
			return 0;
		};
		virtual unsigned GetVertexElementCount() {
			return sizeof(Core::Vertex) / sizeof(float);
		};
	};


	glm::vec3 CalculateTangent(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3);
	void CalculateTangent(std::vector<Core::Vertex>& vertices);

}