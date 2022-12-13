#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shader.hpp"
#include "../model/pyramid/pyramid.hpp"
#include "../model/assimp_model/assimp_model.hpp"
#include "../model/imodel.hpp"
#include "../model/quad/quad.hpp"
#include "../camera/camera.hpp"

namespace Core {

    class Renderer {
    public:
        glm::vec2 m_FramebufferSize;

        Core::Pyramid m_PyramidModel;
        Core::Quad m_GroundModel;

        Core::Material m_PyramidMaterial;
        Core::Material m_SandMaterial;

        void RenderPointLight(Core::Model& model, PointLight& light, Shader& shader, float angle = 0.0f);
        void RenderPyramid(Shader& shader, glm::vec3 position, glm::vec3 scale, float angle = 0.0f);
        void RenderGround(Shader& shader);
        void RenderMoon(Core::Model& model, DirectionalLight& light, Shader& shader, OrbitalCamera* camera);

        void Render(Core::IModel& model, Shader& shader);
    };

}