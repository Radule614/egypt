#pragma once
#include "irenderable.hpp"
#include "../model/model.hpp"

class Renderer {
public:
    unsigned m_CurrRenderableIdx;
    IRenderable* m_CurrRenderable;
    std::vector<IRenderable*> m_Renderables;
    glm::vec2 m_FramebufferSize;
    float m_ScalingFactor;
};