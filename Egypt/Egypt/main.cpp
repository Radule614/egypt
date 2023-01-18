#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "window.hpp"
#include "core/model/assimp_model/assimp_model.hpp"
#include "core/model/pyramid/pyramid.hpp"
#include "core/camera/camera.hpp"
#include "core/renderer/renderer.hpp"
#include "core/model/quad/quad.hpp"
#include "core/model/cube/cube.hpp"
#include "utility/utility.hpp"
#include "core/skybox/skybox.hpp"

int main() {
    GLFWwindow* Window = Window::Setup();
    if (Window == nullptr) return -1;

    EngineState::EngineState& State = EngineState::State;
    Core::OrbitalCamera* Camera = State.m_Camera;
    Core::Renderer* Renderer = State.m_Renderer;

    Core::Model Giant("assets/giant/giant.obj");
    Core::Model Moon("assets/moon/moon.obj");
    Core::Model Skull("assets/skull/skull.obj");
    Core::Model Carpet("assets/carpet/carpet.obj");
    Core::Model Sphere("assets/sphere/sphere.obj");
    
    float RenderDistance = 400.0f;
    glm::mat4 ModelMatrix(1.0f);
    glm::mat4 FreeView = glm::lookAt(Camera->m_Position, Camera->m_Position + Camera->m_Front, Camera->m_Up);
    glm::mat4 Perspective = glm::perspective(45.0f, Renderer->m_FramebufferSize.x / (float)Renderer->m_FramebufferSize.y, 0.1f, RenderDistance);

    Core::DirectionalLight MoonLight = { glm::normalize(glm::vec3(-1.0f, -0.3f, 0.5f)), glm::vec3(0.001f, 0.001f, 0.002f), glm::vec3(0.01f, 0.01f, 0.02f), glm::vec3(0.04f, 0.04f, 0.2f) };
    std::vector<Core::PointLight> PointLights {
        { glm::vec3(-40.0f, 19.0f, 12.0f), Utility::FromRGB(255, 255, 0) },
        { glm::vec3(30.0f, 23.0f, -32.0f), Utility::FromRGB(0, 255, 255) },
        { glm::vec3(-45.0f, 23.0f, -44.0f), Utility::FromRGB(255, 0, 255) },
        { glm::vec3(26.0f, 23.5f, 24.0f), Utility::FromRGB(255, 255, 255) },
        { glm::vec3(25.0f, 5.5f, -8.0f), Utility::FromRGB(255, 50, 0) },
        { glm::vec3(-50.0f, 6.5f, -12.0f), Utility::FromRGB(100, 255, 0) },
        { glm::vec3(-31.0f, 5.5f, -32.0f), Utility::FromRGB(50, 180, 255) },
        { glm::vec3(12.0f, 5.5f, -17.0f), Utility::FromRGB(255, 100, 0) },
    };

    std::vector<Core::SpotLight> SpotLights {};
    for (int i = 0; i < 4; i++) 
        SpotLights.push_back(Core::SpotLight(PointLights[i].position, glm::vec3(0), 0.6f * PointLights[i].diffuse, PointLights[i].diffuse));
    
    Core::Shader MaterialShader("shaders/material.vert", "shaders/material.frag");
    Core::Shader MoonShader("shaders/moon.vert", "shaders/moon.frag");
    Core::Shader SkyboxShader("shaders/skybox.vert", "shaders/skybox.frag");

    Core::Skybox Skybox(SkyboxShader);

    glUseProgram(MaterialShader.GetId());
    MaterialShader.SetProjection(Perspective);
    MaterialShader.SetDirectionalLight("directionalLight", MoonLight);
    for(int i = 0; i < PointLights.size(); i++)
        MaterialShader.SetPointLight("pointLights[" + std::to_string(i) + "]", PointLights[i]);
    for (int i = 0; i < SpotLights.size(); i++)
        MaterialShader.SetSpotLight("spotLights[" + std::to_string(i) + "]", SpotLights[i]);

    glUseProgram(MoonShader.GetId());
    MoonShader.SetProjection(Perspective);
    glUseProgram(SkyboxShader.GetId());
    SkyboxShader.SetProjection(Perspective);
    
    glUseProgram(0);

    float Carpet_X = 0.0f;
    float Carpet_Y = 2.0f;
    float Carpet_Z = 0.0f;
    float AnimationFrame = 0;
    float PointLightAngle = 0;
    float PulseFrame = 0;
    float ShouldPulse = false;
    
    float FrameStartTime = glfwGetTime();
    float FrameEndTime = glfwGetTime();
    float dt = FrameEndTime - FrameStartTime;
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
        glClearColor(0, 0.04, 0.07, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        FrameStartTime = glfwGetTime();
        
        Window::CalculateCameraMoveDirection(dt);

        if (State.PressedKeys[GLFW_KEY_LEFT])
            Carpet_X -= 50.0f * dt;
        if (State.PressedKeys[GLFW_KEY_RIGHT])
            Carpet_X += 50.0f * dt;
        if (State.PressedKeys[GLFW_KEY_UP])
            Carpet_Z -= 50.0f * dt;
        if (State.PressedKeys[GLFW_KEY_DOWN])
            Carpet_Z += 50.0f * dt;
        if (State.PressedKeys[GLFW_KEY_R]) 
            ShouldPulse = false;
        if (State.PressedKeys[GLFW_KEY_T])
            ShouldPulse = true;

        glUseProgram(MaterialShader.GetId());
        FreeView = glm::lookAt(Camera->m_Position, Camera->m_Position + Camera->m_Front, Camera->m_Up);
        MaterialShader.SetView(FreeView);
        MaterialShader.SetVec3("cameraPos", Camera->m_Position);
        glm::vec3 CarpetPosition = glm::vec3(Carpet_X, 2.5f + 2.0 * sin(AnimationFrame), Carpet_Z);
        for (int i = 0; i < SpotLights.size(); i++) {
            SpotLights[i].direction = CarpetPosition - SpotLights[i].position;
            MaterialShader.SetVec3("spotLights[" + std::to_string(i) + "].direction", SpotLights[i].direction);
        }

        Renderer->RenderPyramid(MaterialShader, glm::vec3(30.0f, 0.0f, -32.0f), glm::vec3(36.0f), -25.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(26.0f, 0.0f, 24.0f), glm::vec3(35.0f), 45.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-40.0f, 0.0f, 12.0f), glm::vec3(29.0f));
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-45.0f, 0.0f, -44.0f), glm::vec3(35.0f), 117.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-40.0f, 0.0f, 52.0f), glm::vec3(17.0f), 231.0f);
        
        Renderer->RenderGround(MaterialShader);

        glUseProgram(MaterialShader.GetId());
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, CarpetPosition);
        MaterialShader.SetModel(ModelMatrix);
        Carpet.Render(MaterialShader);
        Skull.Render(MaterialShader);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(20.0f, 0.0f, -15.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        MaterialShader.SetModel(ModelMatrix);
        Giant.Render(MaterialShader);
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-32.0f, 0.0f, 45.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(140.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        MaterialShader.SetModel(ModelMatrix);
        Giant.Render(MaterialShader);
        
        float val = (float)(glm::cos(PulseFrame * 0.01) + 1) / 2.0f;
        for (int i = 0; i < PointLights.size(); i++) {
            if (ShouldPulse) {
                MaterialShader.SetVec3("pointLights[" + std::to_string(i) + "].ambient", PointLights[i].ambient * val);
                MaterialShader.SetVec3("pointLights[" + std::to_string(i) + "].diffuse", PointLights[i].diffuse * val);
                MaterialShader.SetVec3("pointLights[" + std::to_string(i) + "].specular", PointLights[i].specular * val);
            }
            Renderer->RenderPointLight(Skull, PointLights[i], MaterialShader, i * 60 + PointLightAngle);
        }
        for (int i = 0; i < SpotLights.size(); i++) {
            if (ShouldPulse) {
                MaterialShader.SetVec3("spotLights[" + std::to_string(i) + "].ambient", SpotLights[i].ambient * val);
                MaterialShader.SetVec3("spotLights[" + std::to_string(i) + "].diffuse", SpotLights[i].diffuse * val);
                MaterialShader.SetVec3("spotLights[" + std::to_string(i) + "].specular", SpotLights[i].specular * val);
            }
        }

        glUseProgram(MoonShader.GetId());
        MoonShader.SetView(FreeView);
        Renderer->RenderMoon(Moon, MoonLight, MoonShader, Camera);

        glUseProgram(SkyboxShader.GetId());
        SkyboxShader.SetView(glm::mat4(glm::mat3(FreeView)));
        Skybox.Render();

        glUseProgram(0);
        glfwSwapBuffers(Window);
        FrameEndTime = glfwGetTime();
        dt = FrameEndTime - FrameStartTime;
        if (dt < Settings::TargetFPS) {
            int DeltaMS = (int)((Settings::TargetFrameTime - dt) * 1e3f);
            std::this_thread::sleep_for(std::chrono::milliseconds(DeltaMS));
            FrameEndTime = glfwGetTime();
        }
        dt = FrameEndTime - FrameStartTime;
        AnimationFrame += 4 * dt;
        PointLightAngle += 150 * dt;
        if (ShouldPulse)
            PulseFrame += 200 * dt;
    }

    glfwTerminate();
    return 0;
}