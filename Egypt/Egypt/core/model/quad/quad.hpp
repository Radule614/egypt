#pragma once

#include "../../renderer/irenderable.hpp"
#include "../buffer/buffer.hpp"

class Quad : public IRenderable {
public:
	Quad();

	virtual void Render();
private:
	Buffer* m_Buffer;
};