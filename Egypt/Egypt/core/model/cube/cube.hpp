#pragma once
#include "../buffer/buffer.hpp"
#include <vector>

#include "cubebuffer.hpp"
#include "../../renderer/irenderable.hpp"

class Cube : public IRenderable {
public:
    Cube();
    void Render();
private:
    Buffer* mBuffer;

};