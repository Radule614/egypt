#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

out vertex_out {
	vec3 FragNormal;
	vec3 FragPos;
	vec2 FragTexCoords;
	mat3 TBN;
} VertexOut;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
	vec4 pos = uModel * vec4(aPos, 1.0f);

	vec3 normal = aNormal;
	vec3 tangent = aTangent;

	vec3 T = normalize(vec3(uModel * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(uModel * vec4(normal, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	VertexOut.FragPos = vec3(pos);
	VertexOut.FragTexCoords = aTexCoords;
	VertexOut.FragNormal = normal;
	VertexOut.TBN = mat3(T, B, N);

	gl_Position = uProjection * uView * pos;
}