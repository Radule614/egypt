#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "settings.hpp"
#include "state.hpp"
#include <map>

namespace Window {

    static void ChangeKeyStatus(GLFWwindow* window, int key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) 
            EngineState::State.PressedKeys[key] = true;
        else
            EngineState::State.PressedKeys[key] = false;
    }

    static std::vector<int> NeededKeys = {
        GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_R, GLFW_KEY_T
    };

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
        for (int i = 0; i < NeededKeys.size(); i++)
            ChangeKeyStatus(window, NeededKeys[i]);

    }

    static float lastX = Settings::WindowWidth / 2.0;
    static float lastY = Settings::WindowHeight / 2.0;
    static bool FirstMouse = true;

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos)
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
        EngineState::State.m_Camera->CalculateDirection(xoffset, yoffset);
    }

    static void CalculateCameraMoveDirection(float delta) {
        std::map<unsigned int, bool>& PressedKeys = EngineState::State.PressedKeys;
        if (PressedKeys[GLFW_KEY_W] || PressedKeys[GLFW_KEY_S] || PressedKeys[GLFW_KEY_D] || PressedKeys[GLFW_KEY_A])
            EngineState::State.m_Camera->CalculateMoveDirection(PressedKeys, delta);
    }

    static void ErrorCallback(int error, const char* description) {
        std::cerr << "GLFW Error: " << description << std::endl;
    }

	GLFWwindow* Setup() {
        GLFWwindow* Window = 0;
        if (!glfwInit()) {
            std::cerr << "Failed to init glfw" << std::endl;
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSetErrorCallback(ErrorCallback);

        Window = glfwCreateWindow(Settings::WindowWidth, Settings::WindowHeight, Settings::WindowTitle.c_str(), 0, 0);
        if (!Window) {
            std::cerr << "Failed to create window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(Window);
        glfwSetKeyCallback(Window, KeyCallback);
        glfwSetCursorPosCallback(Window, MouseCallback);
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetWindowUserPointer(Window, &EngineState::State);

        GLenum GlewError = glewInit();
        if (GlewError != GLEW_OK) {
            std::cerr << "Failed to init glew: " << glewGetErrorString(GlewError) << std::endl;
            glfwTerminate();
            return nullptr;
        }

        EngineState::Init();

        glViewport(0, 0, EngineState::State.m_Renderer->m_FramebufferSize.x, EngineState::State.m_Renderer->m_FramebufferSize.y);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);

        return Window;
	}

}