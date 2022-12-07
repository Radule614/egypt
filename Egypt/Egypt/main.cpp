#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "core/shader.hpp"
#include "core/model/model.hpp"
#include "core/model/pyramid/pyramid.h"
#include "core/camera/camera.hpp"
#include "core/renderer/renderer.hpp"

const int WindowWidth = 1270;
const int WindowHeight = 720;
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
OrbitalCamera Camera(45.0f, glm::vec3(0.0f, 0.0f, 1.0f), 5.0f);

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

    Shader Basic("shaders/basic.vert", "shaders/basic.frag");

    Pyramid pyr;

    Renderer renderer;
    renderer.m_FramebufferSize = glm::vec2(WindowWidth, WindowHeight);
    renderer.m_Renderables.push_back(&pyr);
    renderer.m_CurrRenderable = renderer.m_Renderables[0];
    renderer.m_ScalingFactor = 1.0f;

    
    float RenderDistance = 100.0f;
    glm::mat4 ModelMatrix(1.0f);
    glm::mat4 FreeView = glm::lookAt(Camera.m_Position, Camera.m_Position + Camera.m_Front, Camera.m_Up);
    glm::mat4 Perspective = glm::perspective(45.0f, renderer.m_FramebufferSize.x / (float)renderer.m_FramebufferSize.y, 0.1f, RenderDistance);
    glUseProgram(Basic.GetId());
    Basic.SetProjection(Perspective);
    glUseProgram(0);
    
    
    State.m_Renderer = &renderer;
    State.m_Camera = &Camera;

    glViewport(0, 0, renderer.m_FramebufferSize.x, renderer.m_FramebufferSize.y);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //glCullFace(GL_BACK);
    float FrameStartTime = glfwGetTime();
    float FrameEndTime = glfwGetTime();
    float dt = FrameEndTime - FrameStartTime;
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        FrameStartTime = glfwGetTime();

        if (PressedKeys[GLFW_KEY_W] || PressedKeys[GLFW_KEY_S] || PressedKeys[GLFW_KEY_D] || PressedKeys[GLFW_KEY_A])
            Camera.CalculateMoveDirection(PressedKeys, dt);
        
        glUseProgram(Basic.GetId());
        FreeView = glm::lookAt(Camera.m_Position, Camera.m_Position + Camera.m_Front, Camera.m_Up);
        Basic.SetView(FreeView);


        
        
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, -2.0f));
        Basic.SetModel(ModelMatrix);
        State.m_Renderer->m_CurrRenderable->Render();

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
    }

    glfwTerminate();
    return 0;
}



