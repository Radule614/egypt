#include "cubebuffer.hpp"

std::vector<float> CubeBuffer::mVertices = {
    //     POS        |      NORMALS   
    // X    Y      Z       X    Y     Z
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
    
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,-1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,-1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f,0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
};

CubeBuffer::CubeBuffer() {}

float*
CubeBuffer::GetVertices() {
	return mVertices.data();
}

unsigned
CubeBuffer::GetVertexCount() {
	return mVertices.size();
}

unsigned
CubeBuffer::GetVertexElementCount() {
	return 6;
}