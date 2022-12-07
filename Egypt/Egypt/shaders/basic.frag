#version 330 core

in vertex_out {
	vec3 FragColour;
} FragmentIn;

out vec4 FragColour;

void main() {
	FragColour = vec4(FragmentIn.FragColour, 1.0f);
}