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

    void Reset() {
        if (m_Renderables.size() == 0) 
            return;
        m_CurrRenderableIdx = 0;
        m_CurrRenderable = m_Renderables[0];
    }

    void RenderNext() {
        if (m_Renderables.size() <= m_CurrRenderableIdx + 1) 
            return;
        
        m_CurrRenderableIdx += 1;
        m_CurrRenderable = m_Renderables[m_CurrRenderableIdx];
        m_CurrRenderable->Render();
    }

    void RenderCurrent() {
        m_CurrRenderable->Render();
    }
};