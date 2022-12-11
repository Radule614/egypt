#include "renderer.hpp"

void Renderer::RenderPointLight(Model& model, PointLight& light, Shader& shader) {
    glUseProgram(shader.GetId());

    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, light.position);
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f));
    shader.SetVec3("lightColor", light.diffuse);
    shader.SetModel(ModelMatrix);
    model.Render(shader);
}


void Renderer::RenderPyramid(Shader& shader, glm::vec3 position, glm::vec3 scale, float angle) {
    glUseProgram(shader.GetId());
    shader.SetMaterial("material", m_PyramidMaterial);
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    if(angle != 0)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, scale);
    shader.SetModel(ModelMatrix);
    m_PyramidModel.Render();
}
