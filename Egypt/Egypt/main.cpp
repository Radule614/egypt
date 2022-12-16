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

int main() {
    GLFWwindow* Window = Window::Setup();
    if (Window == nullptr) return -1;

    EngineState::EngineState& State = EngineState::State;
    Core::OrbitalCamera* Camera = State.m_Camera;
    Core::Renderer* Renderer = State.m_Renderer;

    Core::Cube LightModel;
    Core::Material PyrMaterial = { glm::vec3(0.04f, 0.04f, 0.1f), glm::vec3(0.6f, 0.6f, 0.3f), glm::vec3(0.3f, 0.3f, 0.2f), 128.0f };
    Core::Material SandMaterial = { glm::vec3(0.04f, 0.04f, 0.0f), glm::vec3(0.4f, 0.4f, 0.2f), glm::vec3(0.3f, 0.3f, 0.2f), 128.0f };

    Renderer->m_PyramidMaterial = PyrMaterial;
    Renderer->m_SandMaterial = SandMaterial;

    Core::Model Carpet("assets/carpet/carpet.obj");
    Core::Model Sphere("assets/sphere/sphere.obj");
    Core::Model Skull("assets/skull/skull.obj");
    Core::Model Giant("assets/giant/Stone.obj");
    
    float RenderDistance = 300.0f;
    glm::mat4 ModelMatrix(1.0f);
    glm::mat4 FreeView = glm::lookAt(Camera->m_Position, Camera->m_Position + Camera->m_Front, Camera->m_Up);
    glm::mat4 Perspective = glm::perspective(45.0f, Renderer->m_FramebufferSize.x / (float)Renderer->m_FramebufferSize.y, 0.1f, RenderDistance);

    Core::DirectionalLight MoonLight = { glm::normalize(glm::vec3(-1.0f, -0.3f, 0.5f)), glm::vec3(0.001f, 0.001f, 0.002f), glm::vec3(0.03f, 0.03f, 0.05f), glm::vec3(0.04f, 0.04f, 0.2f) };
    std::vector<Core::PointLight> PointLights {
        { glm::vec3(25.0f, 5.5f, -8.0f), glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(-50.0f, 6.5f, -12.0f), glm::vec3(0.4f, 1.0f, 0.0f) },
        { glm::vec3(-40.0f, 20.0f, 12.0f), glm::vec3(1.0f, 0.2f, 0.0f) },
        { glm::vec3(-25.0f, 5.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) },
        { glm::vec3(-25.0f, 5.5f, 20.0f), glm::vec3(0.8f, 0.4f, 1.0f) },
        { glm::vec3(-31.0f, 5.5f, -32.0f), glm::vec3(0.2f, 0.7f, 1.0f) },
        { glm::vec3(12.0f, 5.5f, -17.0f), glm::vec3(1.0f, 0.4f, 0.0f) }
    };

    Core::Shader MaterialShader("shaders/material.vert", "shaders/material.frag");
    Core::Shader LightShader("shaders/light.vert", "shaders/light.frag");

    glUseProgram(MaterialShader.GetId());
    MaterialShader.SetProjection(Perspective);
    for(int i = 0; i < PointLights.size(); i++)
        MaterialShader.SetPointLight("pointLights[" + std::to_string(i) + "]", PointLights[i]);
    MaterialShader.SetDirectionalLight("directionalLight", MoonLight);

    glUseProgram(LightShader.GetId());
    LightShader.SetProjection(Perspective);
    
    glUseProgram(0);

    float Carpet_X = 0.0f;
    float Carpet_Y = 2.0f;
    float Carpet_Z = 0.0f;
    float AnimationFrame = 0;
    float PointLightAngle = 0;
    
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

        glUseProgram(MaterialShader.GetId());
        FreeView = glm::lookAt(Camera->m_Position, Camera->m_Position + Camera->m_Front, Camera->m_Up);
        MaterialShader.SetView(FreeView);
        MaterialShader.SetVec3("cameraPos", Camera->m_Position);

        Renderer->RenderPyramid(MaterialShader, glm::vec3(30.0f, 0.0f, -32.0f), glm::vec3(36.0f), -25.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(26.0f, 0.0f, 24.0f), glm::vec3(35.0f), 45.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-40.0f, 0.0f, 12.0f), glm::vec3(29.0f));
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-45.0f, 0.0f, -44.0f), glm::vec3(35.0f), 117.0f);
        Renderer->RenderPyramid(MaterialShader, glm::vec3(-40.0f, 0.0f, 52.0f), glm::vec3(17.0f), 231.0f);

        Renderer->RenderGround(MaterialShader);
        
        glUseProgram(MaterialShader.GetId());
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(Carpet_X, 2.0f + 0.6 * sin(AnimationFrame), Carpet_Z));
        MaterialShader.SetModel(ModelMatrix);
        Carpet.Render(MaterialShader);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(Carpet_X, 4.0f + 0.6 * sin(AnimationFrame), Carpet_Z));
        Skull.Render(MaterialShader);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(20.0f, 0.0f, -15.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        MaterialShader.SetModel(ModelMatrix);
        Giant.Render(MaterialShader);
        
        for (int i = 0; i < PointLights.size(); i++)
            Renderer->RenderPointLight(Skull, PointLights[i], MaterialShader, i * 60 + PointLightAngle);

        glUseProgram(LightShader.GetId());
        LightShader.SetView(FreeView);
        
        Renderer->RenderMoon(Sphere, MoonLight, LightShader, Camera);

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
    }

    glfwTerminate();
    return 0;
}