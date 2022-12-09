#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vertex_out {
	vec3 FragNormal;
	vec3 FragPos;
	vec2 FragTexCoords;
} VertexOut;

void main() {
	vec4 pos = uModel * vec4(aPos, 1.0f);
	gl_Position = uProjection * uView * pos;
	VertexOut.FragNormal = aNormal;
	VertexOut.FragPos = vec3(pos);
	VertexOut.FragTexCoords = aTexCoords;
}