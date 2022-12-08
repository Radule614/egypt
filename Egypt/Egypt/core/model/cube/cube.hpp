/**
 * @file cube.hpp
 * @author Jovan Ivosevic
 * @brief Cube
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../buffer/buffer.hpp"
#include <vector>

#include "cubebuffer.hpp"
#include "../../renderer/irenderable.hpp"

class Cube : public IRenderable {
public:

    /**
     * @brief Initializes cube buffer
     *
     */
    Cube();


    /**
     * @brief IRenderable Render implementation
     *
     */
    void Render();
private:
    Buffer* mBuffer;

};