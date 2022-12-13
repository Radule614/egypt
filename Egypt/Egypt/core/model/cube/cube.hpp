#pragma once

#include "cubebuffer.hpp"
#include "../../shader.hpp"
#include "../imodel.hpp"

namespace Core {
    class Cube : public IModel {
    public:
        Cube();

        void Render(Shader& shader);
    };
}
