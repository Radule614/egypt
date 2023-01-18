#include "shader.hpp"

Core::Shader::Shader(const std::string& vShaderPath, const std::string& fShaderPath) {
    unsigned vs = loadAndCompileShader(vShaderPath, GL_VERTEX_SHADER);
    unsigned fs = loadAndCompileShader(fShaderPath, GL_FRAGMENT_SHADER);
    m_Id = createBasicProgram(vs, fs);
}

void Core::Shader::SetUniform4m(const std::string& uniform, const glm::mat4& m) const {
    glUniformMatrix4fv(glGetUniformLocation(m_Id, uniform.c_str()), 1, GL_FALSE, &m[0][0]);
}

void Core::Shader::SetModel(const glm::mat4& m) const {
    SetUniform4m("uModel", m);
}

void Core::Shader::SetView(const glm::mat4& m) const {
    SetUniform4m("uView", m);
}

void Core::Shader::SetProjection(const glm::mat4& m) const {
    SetUniform4m("uProjection", m);
}

void Core::Shader::SetVec3(const std::string& uniform, const glm::vec3& v) const {
    glUniform3fv(glGetUniformLocation(m_Id, uniform.c_str()), 1, &v[0]);
}

void Core::Shader::SetVec3(const std::string& uniform, float x, float y, float z) const {
    SetVec3(uniform, glm::vec3(x, y, z));
}

void Core::Shader::SetFloat(const std::string& uniform, float x) const {
    glUniform1f(glGetUniformLocation(m_Id, uniform.c_str()), x);
}

void Core::Shader::SetInt(const std::string& uniform, int i) const
{
    glUniform1i(glGetUniformLocation(m_Id, uniform.c_str()), i);
}

void Core::Shader::SetMaterial(const std::string& uniform, Core::Material& material) const {
    SetVec3(uniform + ".ambient", material.ambient);
    SetVec3(uniform + ".diffuse", material.diffuse);
    SetVec3(uniform + ".specular", material.specular);
    SetFloat(uniform + ".shininess", material.shininess);
}
void Core::Shader::SetPointLight(const std::string& uniform, Core::PointLight& light) const {
    SetVec3(uniform + ".position", light.position);
    SetVec3(uniform + ".ambient", light.ambient);
    SetVec3(uniform + ".diffuse", light.diffuse);
    SetVec3(uniform + ".specular", light.specular);
    SetFloat(uniform + ".constant", light.constant);
    SetFloat(uniform + ".linear", light.linear);
    SetFloat(uniform + ".quadratic", light.quadratic);
}

void Core::Shader::SetDirectionalLight(const std::string& uniform, Core::DirectionalLight& light) const {
    SetVec3(uniform + ".direction", light.direction);
    SetVec3(uniform + ".ambient", light.ambient);
    SetVec3(uniform + ".diffuse", light.diffuse);
    SetVec3(uniform + ".specular", light.specular);
}

void Core::Shader::SetSpotLight(const std::string& uniform, Core::SpotLight& light) const {
    SetVec3(uniform + ".direction", light.direction);
    SetVec3(uniform + ".position", light.position);
    SetVec3(uniform + ".ambient", light.ambient);
    SetVec3(uniform + ".diffuse", light.diffuse);
    SetVec3(uniform + ".specular", light.specular);
    SetFloat(uniform + ".cutOff", light.cutOff);
    SetFloat(uniform + ".outerCutOff", light.outerCutOff);
    SetFloat(uniform + ".constant", light.constant);
    SetFloat(uniform + ".linear", light.linear);
    SetFloat(uniform + ".quadratic", light.quadratic);
}

unsigned Core::Shader::GetId() const {
    return m_Id;
}

unsigned Core::Shader::loadAndCompileShader(std::string filename, GLuint shaderType) {
    unsigned ShaderID = 0;
    std::ifstream In(filename);
    std::string Str;

    In.seekg(0, std::ios::end);
    Str.reserve(In.tellg());
    In.seekg(0, std::ios::beg);

    Str.assign((std::istreambuf_iterator<char>(In)), std::istreambuf_iterator<char>());
    const char* CharContent = Str.c_str();

    ShaderID = glCreateShader(shaderType);
    glShaderSource(ShaderID, 1, &CharContent, NULL);
    glCompileShader(ShaderID);

    int Success;
    char InfoLog[512];
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);
    if (!Success) {
        glGetShaderInfoLog(ShaderID, 256, NULL, InfoLog);
        std::string ShaderTypeName = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cout << "Error while compiling shader [" << ShaderTypeName << "]:" << std::endl << InfoLog << std::endl;
        return 0;
    }

    std::cout << "LOADED: " << filename << std::endl;

    return ShaderID;
}

unsigned Core::Shader::createBasicProgram(unsigned vShader, unsigned fShader) {
    unsigned ProgramID = 0;
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vShader);
    glAttachShader(ProgramID, fShader);
    glLinkProgram(ProgramID);

    int Success;
    char InfoLog[512];
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ProgramID, 512, NULL, InfoLog);
        std::cerr << "[Err] Failed to link shader program:" << std::endl << InfoLog << std::endl;
        return 0;
    }

    glDetachShader(ProgramID, vShader);
    glDetachShader(ProgramID, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return ProgramID;
}