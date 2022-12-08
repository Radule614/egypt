#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
}