#pragma once

#include "../../shader.hpp"
#include "../imodel.hpp"
#include "quad_buffer.hpp"

namespace Core {

	class Quad : public IModel {
	public:
		Quad();

		virtual void Render(Shader& shader);
	};

}
