#pragma once

#include "utility.hpp"

glm::vec3 Utility::FromRGB(float r, float g, float b)
{
	if (r > 255.0f) r = 255.0f;
	if (g > 255.0f) g = 255.0f;
	if (b > 255.0f) b = 255.0f;
	if (r < 0.0f) r = 0.0f;
	if (g < 0.0f) g = 0.0f;
	if (b < 0.0f) b = 0.0f;
	return glm::vec3(r/255.0f, g/255.0f, b/255.0f);
}

void Utility::PrintVec3(glm::vec3 v)
{
	std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}
