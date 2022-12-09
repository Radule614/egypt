#pragma once

#include "../../renderer/irenderable.hpp"
#include "../buffer/buffer.hpp"

class Pyramid : public IRenderable {
public:
	Pyramid();

	virtual void Render();
private:
	Buffer* m_Buffer;
};