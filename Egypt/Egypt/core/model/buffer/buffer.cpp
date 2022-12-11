#include "buffer.hpp"

Buffer::Buffer(IBufferable& bufferable) : mEBO(0) {
    mIndexCount = bufferable.GetIndexCount();
    mVertexCount = bufferable.GetVertexCount();
    int mVertexElementCount = bufferable.GetVertexElementCount();
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertexCount* mVertexElementCount * sizeof(float), &(bufferable.GetVertices().data())[0], GL_STATIC_DRAW);

    float Stride = bufferable.GetVertexElementCount() * sizeof(float);

    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(TEXCOORD_LOCATION);
    glVertexAttribPointer(TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(TANGENT_LOCATION);
    glVertexAttribPointer(TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    if (mIndexCount) {
        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferable.GetIndexCount() * sizeof(float), bufferable.GetIndices(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void
Buffer::Render() {
    glBindVertexArray(mVAO);
    if (mIndexCount) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, (void*)0);
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
}