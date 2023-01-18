#version 330 core

in vertex_out {
	vec2 FragTexCoords;
} FragmentIn;

out vec4 FragColour;

uniform sampler2D texture_diffuse1;

void main() {
	FragColour = texture(texture_diffuse1, FragmentIn.FragTexCoords);
}