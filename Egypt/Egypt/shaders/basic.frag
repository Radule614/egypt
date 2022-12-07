#version 330 core

in vertex_out {
	vec3 FragNormal;
} FragmentIn;

out vec4 FragColour;

void main() {
	FragColour = vec4((FragmentIn.FragNormal + 1)/2.0f, 1.0f);
	//FragColour = vec4(1.0f);
}