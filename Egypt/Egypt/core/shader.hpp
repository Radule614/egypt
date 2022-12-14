#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "model/material.hpp"

namespace Core {

    class Shader {
    public:
        static const unsigned POSITION_LOCATION = 0;
        static const unsigned COLOR_LOCATION = 1;
        Shader(const std::string& vShaderPath, const std::string& fShaderPath);

        unsigned GetId() const;
        void SetUniform4m(const std::string& uniform, const glm::mat4& m) const;
        void SetModel(const glm::mat4& m) const;
        void SetView(const glm::mat4& m) const;
        void SetProjection(const glm::mat4& m) const;

        void SetVec3(const std::string&, const glm::vec3&) const;
        void SetVec3(const std::string&, float, float, float) const;
        void SetFloat(const std::string&, float) const;
        void SetInt(const std::string&, int) const;

        void SetMaterial(const std::string&, Core::Material) const;
        void SetPointLight(const std::string&, Core::PointLight) const;
        void SetDirectionalLight(const std::string&, Core::DirectionalLight) const;
    private:
        unsigned m_Id;
        unsigned loadAndCompileShader(std::string filename, GLuint shaderType);
        unsigned createBasicProgram(unsigned vShader, unsigned fShader);
    };

}