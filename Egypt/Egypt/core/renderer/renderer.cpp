#include "renderer.hpp"

void Core::Renderer::RenderPointLight(Core::Model& model, PointLight& light, Shader& shader, float angle) {
    glUseProgram(shader.GetId());

    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, light.position);
    if(angle != 0)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.9f));
    //shader.SetVec3("lightColor", light.diffuse);
    shader.SetModel(ModelMatrix);
    model.Render(shader);
}


void Core::Renderer::RenderPyramid(Shader& shader, glm::vec3 position, glm::vec3 scale, float angle) {
    glUseProgram(shader.GetId());
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    if(angle != 0)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, scale);
    shader.SetModel(ModelMatrix);
    m_PyramidModel.SetModelMatrix(ModelMatrix);
    m_PyramidModel.Render(shader);
}

void Core::Renderer::RenderGround(Shader& shader)
{
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(200.0f, 1.0f, 200.0f));
    m_GroundModel.SetModelMatrix(ModelMatrix);
    m_GroundModel.Render(shader);
}

void Core::Renderer::RenderMoon(Core::Model& model, DirectionalLight& light, Shader& shader, OrbitalCamera* camera)
{
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, -200.0f * light.direction);
    ModelMatrix = glm::translate(ModelMatrix, camera->m_Position);
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5.3f));
    shader.SetVec3("lightColor", glm::vec3(0.35f, 0.45f, 0.64f));
    shader.SetModel(ModelMatrix);
    model.Render(shader);
}

void Core::Renderer::Render(Core::IModel& model, Shader& shader) {
    glUseProgram(shader.GetId());
}
