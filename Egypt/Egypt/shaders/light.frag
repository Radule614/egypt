#version 330 core

out vec4 FragColour;

uniform vec3 lightColor;

void main() {
	FragColour = vec4(lightColor, 1.0);
}