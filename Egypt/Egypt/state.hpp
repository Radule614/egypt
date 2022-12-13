#pragma once
#include "core/camera/camera.hpp"
#include "core/renderer/renderer.hpp"

namespace EngineState {

    struct EngineState {
        Core::OrbitalCamera* m_Camera;
        Core::Renderer* m_Renderer;
        std::map<unsigned int, bool> PressedKeys;
        float m_DT;
    };

    static EngineState State;

    static void Init() {
		Core::OrbitalCamera* Camera = new Core::OrbitalCamera(45.0f, glm::vec3(-10.0f, 10.0f, 27.0f), 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        Core::Renderer* Renderer = new Core::Renderer();
        Renderer->m_FramebufferSize = glm::vec2(Settings::WindowWidth, Settings::WindowHeight);

		State.m_Camera = Camera;
        State.m_Renderer = Renderer;
	}
    
}