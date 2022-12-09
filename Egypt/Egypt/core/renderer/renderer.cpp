#include "renderer.hpp"

void Renderer::RenderPointLight(IRenderable& model, PointLight& light, Shader& shader) {
    glUseProgram(shader.GetId());

    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, light.position);
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.7f));
    shader.SetVec3("lightColor", light.diffuse);
    shader.SetModel(ModelMatrix);
    model.Render();
}


void Renderer::RenderPyramid(Shader& shader, glm::vec3 position, glm::vec3 scale) {
    glUseProgram(shader.GetId());
    shader.SetMaterial("material", m_PyramidMaterial);
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::scale(ModelMatrix, scale);
    shader.SetModel(ModelMatrix);
    m_PyramidModel.Render();
}
