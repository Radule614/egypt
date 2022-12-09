#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "core/shader.hpp"
#include "core/model/model.hpp"
#include "core/model/pyramid/pyramid.hpp"
#include "core/camera/camera.hpp"
#include "core/renderer/renderer.hpp"
#include "core/model/quad/quad.hpp"
#include "core/renderer/material.hpp"
#include "core/model/cube/cube.hpp"

const int WindowWidth = 1600;
const int WindowHeight = 900;
const std::string WindowTitle = "Egypt";
const float TargetFPS = 100.0f;
const float TargetFrameTime = 1.0f / TargetFPS;
std::map<unsigned int, bool> PressedKeys;

struct EngineState {
    OrbitalCamera* m_Camera;
    Renderer* m_Renderer;
    float m_DT;
};

EngineState State;
OrbitalCamera Camera(45.0f, glm::vec3(0.0f, 1.0f, 1.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    bool IsDown = action == GLFW_PRESS || action == GLFW_REPEAT;
    switch (key) {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_W] = true;
    else
        PressedKeys[GLFW_KEY_W] = false;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_S] = true;
    else
        PressedKeys[GLFW_KEY_S] = false;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_D] = true;
    else
        PressedKeys[GLFW_KEY_D] = false;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_A] = true;
    else
        PressedKeys[GLFW_KEY_A] = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_LEFT] = true;
    else
        PressedKeys[GLFW_KEY_LEFT] = false;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_RIGHT] = true;
    else
        PressedKeys[GLFW_KEY_RIGHT] = false;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_UP] = true;
    else
        PressedKeys[GLFW_KEY_UP] = false;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        PressedKeys[GLFW_KEY_DOWN] = true;
    else
        PressedKeys[GLFW_KEY_DOWN] = false;
}

float lastX = WindowWidth / 2.0;
float lastY = WindowHeight / 2.0;
bool FirstMouse = true;

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (FirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        FirstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    Camera.CalculateDirection(xoffset, yoffset);
}

float Clamp(float value, float min, float max) {
    return value < min ? min : value > max ? max : value;
}

static void ErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

int main() {
    GLFWwindow* Window = 0;
    if (!glfwInit()) {
        std::cerr << "Failed to init glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(ErrorCallback);

    Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), 0, 0);
    if (!Window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window);
    glfwSetKeyCallback(Window, KeyCallback);
    glfwSetCursorPosCallback(Window, MouseCallback);
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(Window, &State);

    GLenum GlewError = glewInit();
    if (GlewError != GLEW_OK) {
        std::cerr << "Failed to init glew: " << glewGetErrorString(GlewError) << std::endl;
        glfwTerminate();
        return -1;
    }

    Shader BasicShader("shaders/basic.vert", "shaders/basic.frag");
    Shader LightShader("shaders/light.vert", "shaders/light.frag");

    Quad GroundModel;
    Pyramid PyramidModel;
    Cube LightModel;
    Model Carpet("assets/carpet/carpet.obj");

    Material PyrMaterial = { glm::vec3(0.76f, 0.6f, 0.37f), glm::vec3(0.76f, 0.6f, 0.37f), glm::vec3(0.4f, 0.4f, 0.3f), 128.0f };
    Material SandMaterial = { glm::vec3(0.95f, 0.82f, 0.46f), glm::vec3(0.95f, 0.82f, 0.46f), glm::vec3(0.4f, 0.3f, 0.1f), 128.0f };

    Renderer Renderer;
    Renderer.m_FramebufferSize = glm::vec2(WindowWidth, WindowHeight);
    Renderer.m_PyramidModel = PyramidModel;
    Renderer.m_PyramidMaterial = PyrMaterial;
    Renderer.m_SandMaterial = SandMaterial;

    State.m_Renderer = &Renderer;
    State.m_Camera = &Camera;
    
    float RenderDistance = 200.0f;
    glm::mat4 ModelMatrix(1.0f);
    glm::mat4 FreeView = glm::lookAt(Camera.m_Position, Camera.m_Position + Camera.m_Front, Camera.m_Up);
    glm::mat4 Perspective = glm::perspective(45.0f, Renderer.m_FramebufferSize.x / (float)Renderer.m_FramebufferSize.y, 0.1f, RenderDistance);
    glUseProgram(BasicShader.GetId());
    BasicShader.SetProjection(Perspective);

    DirectionalLight moonLight = { glm::normalize(glm::vec3(-1.0f, -0.3f, 0.5f)), glm::vec3(0.01f, 0.01f, 0.03f), glm::vec3(0.2f, 0.2f, 0.9f), glm::vec3(0.2f, 0.2f, 0.7f) };
    std::vector<PointLight> PointLights { 
        { glm::vec3(17.0f, 5.5f, 6.0f), glm::vec3(1.0f, 1.0f, 0.0f) },
        { glm::vec3(7.0f, 5.5f, -17.0f), glm::vec3(0.4f, 1.0f, 0.0f) },
        { glm::vec3(-30.0f, 18.0f, -4.0f), glm::vec3(1.0f, 0.2f, 0.0f) },
        { glm::vec3(-12.0f, 5.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) },
        { glm::vec3(-12.0f, 5.5f, 12.0f), glm::vec3(0.8f, 0.4f, 1.0f) },
        { glm::vec3(-12.0f, 5.5f, -12.0f), glm::vec3(0.2f, 0.7f, 1.0f) }
    };

    for(int i = 0; i < PointLights.size(); i++)
        BasicShader.SetPointLight("pointLights[" + std::to_string(i) + "]", PointLights[i]);
    
    BasicShader.SetDirectionalLight("directionalLight", moonLight);
    
    glUseProgram(LightShader.GetId());
    LightShader.SetProjection(Perspective);
    
    glUseProgram(0);

    float Carpet_X = 0.0f;
    float Carpet_Y = 2.0f;
    float Carpet_Z = 0.0f;
    int CurrentFrame = 0;

    glViewport(0, 0, Renderer.m_FramebufferSize.x, Renderer.m_FramebufferSize.y);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    float FrameStartTime = glfwGetTime();
    float FrameEndTime = glfwGetTime();
    float dt = FrameEndTime - FrameStartTime;
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
        glClearColor(0, 0.07, 0.15, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        FrameStartTime = glfwGetTime();
        if (PressedKeys[GLFW_KEY_W] || PressedKeys[GLFW_KEY_S] || PressedKeys[GLFW_KEY_D] || PressedKeys[GLFW_KEY_A])
            Camera.CalculateMoveDirection(PressedKeys, dt);
        if (PressedKeys[GLFW_KEY_LEFT])
            Carpet_X -= 50.0f * dt;
        if (PressedKeys[GLFW_KEY_RIGHT])
            Carpet_X += 50.0f * dt;
        if (PressedKeys[GLFW_KEY_UP])
            Carpet_Z -= 50.0f * dt;
        if (PressedKeys[GLFW_KEY_DOWN])
            Carpet_Z += 50.0f * dt;
        
        glUseProgram(BasicShader.GetId());
        FreeView = glm::lookAt(Camera.m_Position, Camera.m_Position + Camera.m_Front, Camera.m_Up);
        BasicShader.SetView(FreeView);
        BasicShader.SetVec3("cameraPos", Camera.m_Position);
        BasicShader.SetInt("useTexture", 0);
        
        Renderer.RenderPyramid(BasicShader, glm::vec3(18.0f, 0.0f, -25.0f), glm::vec3(26.0f));
        Renderer.RenderPyramid(BasicShader, glm::vec3(26.0f, 0.0f, 24.0f), glm::vec3(32.0f));
        Renderer.RenderPyramid(BasicShader, glm::vec3(-30.0f, 0.0f, -4.0f), glm::vec3(24.0f));
        
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(150.0f, 1.0f, 150.0f));
        BasicShader.SetModel(ModelMatrix);
        BasicShader.SetMaterial("material", SandMaterial);
        GroundModel.Render();

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(Carpet_X, 2.0f + 0.4*sin(CurrentFrame * 0.05), Carpet_Z));
        BasicShader.SetModel(ModelMatrix);
        BasicShader.SetInt("useTexture", 1);
        Carpet.Render(BasicShader);

        glUseProgram(LightShader.GetId());
        LightShader.SetView(FreeView);
        
        for (int i = 0; i < PointLights.size(); i++)
            Renderer.RenderPointLight(LightModel, PointLights[i], LightShader);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, -50.0f * moonLight.direction);
        ModelMatrix = glm::translate(ModelMatrix, Camera.m_Position);
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3.0f));
        LightShader.SetVec3("lightColor", glm::vec3(0.65f, 0.65f, 0.8f));
        LightShader.SetModel(ModelMatrix);
        LightModel.Render();
        

        glUseProgram(0);
        glfwSwapBuffers(Window);
        FrameEndTime = glfwGetTime();
        dt = FrameEndTime - FrameStartTime;
        if (dt < TargetFPS) {
            int DeltaMS = (int)((TargetFrameTime - dt) * 1e3f);
            std::this_thread::sleep_for(std::chrono::milliseconds(DeltaMS));
            FrameEndTime = glfwGetTime();
        }
        dt = FrameEndTime - FrameStartTime;
        CurrentFrame++;
    }

    glfwTerminate();
    return 0;
}



