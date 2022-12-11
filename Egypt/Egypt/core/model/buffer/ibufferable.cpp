#include "ibufferable.hpp"

glm::vec3 CalculateTangent(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3) {
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	glm::vec3 tangent{};
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	return tangent;
}

void CalculateTangent(std::vector<Vertex>& vertices) {
	if (vertices.size() % 3 != 0) return;
	for (int i = 0; i < vertices.size(); i += 3) {
		glm::vec3& pos1 = vertices[i].Position;
		glm::vec3& pos2 = vertices[i + 1].Position;
		glm::vec3& pos3 = vertices[i + 2].Position;
		glm::vec2& uv1 = vertices[i].TexCoords;
		glm::vec2& uv2 = vertices[i + 1].TexCoords;
		glm::vec2& uv3 = vertices[i + 2].TexCoords;

		glm::vec3 tangent = CalculateTangent(pos1, pos2, pos3, uv1, uv2, uv3);
		vertices[i].Tangent = tangent;
		vertices[i + 1].Tangent = tangent;
		vertices[i + 2].Tangent = tangent;
	}
}