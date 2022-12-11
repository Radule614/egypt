#pragma once
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>

class OrbitalCamera {
public:
    float m_FOV;
    float m_Pitch;
    float m_Yaw;
    float m_RotateSpeed;
    float m_Radius;
    float m_ZoomSpeed;
    glm::vec3 m_WorldUp;
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_Target;
    float m_Velocity;

    OrbitalCamera(float fov, glm::vec3 position, float distance, const glm::vec3& target = glm::vec3(0.0f), float rotateSpeed = 10.0f, float zoomSpeed = 10.0f, const glm::vec3 &worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

    void Rotate(float dYaw, float dPitch, float dt);

    void Zoom(float dy, float dt);
    void CalculateDirection(float& xoffset, float& yoffset);
    void CalculateMoveDirection(std::map<unsigned int, bool>& pressedKeys, float delt);

private:
    void updateVectors();
};