#include "buffer.hpp"

Core::Buffer::Buffer(IBufferable& bufferable) : m_EBO(0), m_ModelMatrix(1.0f) {
    m_IndexCount = bufferable.GetIndexCount();
    m_VertexCount = bufferable.GetVertexCount();
    int mVertexElementCount = bufferable.GetVertexElementCount();
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_VertexCount* mVertexElementCount * sizeof(float), &(bufferable.GetVertices().data())[0], GL_STATIC_DRAW);

    float Stride = bufferable.GetVertexElementCount() * sizeof(float);

    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(TEXCOORD_LOCATION);
    glVertexAttribPointer(TEXCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(TANGENT_LOCATION);
    glVertexAttribPointer(TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    if (m_IndexCount) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferable.GetIndexCount() * sizeof(float), bufferable.GetIndices(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Core::Buffer::AddDiffuseMap(std::string path)
{
    LoadTexture(path, "texture_diffuse");
}

void Core::Buffer::AddSpecularMap(std::string path)
{
    LoadTexture(path, "texture_specular");
}

void Core::Buffer::AddNormalMap(std::string path)
{
    LoadTexture(path, "texture_normal");
}

void Core::Buffer::Render(Shader& shader) {
    glUseProgram(shader.GetId());
    BindTextures(shader);
    shader.SetModel(m_ModelMatrix);
    glBindVertexArray(m_VAO);
    if (m_IndexCount) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, (void*)0);
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Core::Buffer::SetPosition(glm::vec3& pos)
{
    m_ModelMatrix = glm::translate(m_ModelMatrix, pos);
}

void Core::Buffer::SetRotation(glm::vec3& rotationAxis, float angle)
{
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), rotationAxis);
}

void Core::Buffer::SetScale(glm::vec3& scale)
{
    m_ModelMatrix = glm::scale(m_ModelMatrix, scale);
}

void Core::Buffer::SetModelMatrix(glm::mat4& mat)
{
    m_ModelMatrix = mat;
}

void Core::Buffer::SetModelMatrix(glm::vec3& pos, glm::vec3 scale, glm::vec3 rotation, float angle)
{
    SetPosition(pos);
    SetRotation(rotation, angle);
    SetScale(scale);
}

void Core::Buffer::LoadTexture(std::string& path, std::string type)
{
    for (unsigned int i = 0; i < LoadedTextures.size(); i++) {
        if (std::strcmp(LoadedTextures[i].path.data(), path.c_str()) == 0)
        {
            std::cout << "Texture already present: " << LoadedTextures[i].path << std::endl;
            m_Textures.push_back(LoadedTextures[i]);
            return;
        }
    }
    
    Texture texture;
    texture.id = LoadTextureFromFile(path);
    texture.type = type;
    texture.path = path;
    LoadedTextures.push_back(texture);
    m_Textures.push_back(texture);
}

void Core::Buffer::BindTextures(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = m_Textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        shader.SetInt(name + number, i);
        glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
    }
    
    glActiveTexture(GL_TEXTURE0);
}
