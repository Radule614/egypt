#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader.hpp"
#include "../model/pyramid/pyramid.hpp"

class Renderer {
public:
    glm::vec2 m_FramebufferSize;

    Material m_PyramidMaterial;
    Pyramid m_PyramidModel;

    Material m_SandMaterial;
    
    void RenderPointLight(IRenderable& model, PointLight& light, Shader& shader);
    void RenderPyramid(Shader& shader, glm::vec3 position, glm::vec3 scale, float angle = 0.0f);
};