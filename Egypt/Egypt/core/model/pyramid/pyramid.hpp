#pragma once

#include "../../shader.hpp"
#include "../imodel.hpp"
#include "pyramid_buffer.hpp"

namespace Core {
	class Pyramid : public IModel {
	public:
		Pyramid();

		virtual void Render(Shader& shader);
	};
}
