#include "camera.hpp"
#include <iostream>
#include <GLFW/glfw3.h>


OrbitalCamera::OrbitalCamera(float fov, glm::vec3 position, float distance, const glm::vec3& target, float rotateSpeed, float zoomSpeed, const glm::vec3 &worldUp)
    : m_WorldUp(worldUp),
      m_Target(target)  {
    m_FOV = fov;
    m_Radius = distance;
    m_RotateSpeed = rotateSpeed;
    m_ZoomSpeed = zoomSpeed;
    m_WorldUp = worldUp;
    m_Target = target;
    m_Yaw = -90.0f;
    m_Pitch = 0.0f;
    m_Position = position;
    m_Velocity = 30.0f;

    m_Front = glm::normalize(m_Target - m_Position);
    updateVectors();
}

void
OrbitalCamera::Rotate(float dYaw, float dPitch, float dt) {
    dYaw *= m_RotateSpeed * dt;
    dPitch *= m_RotateSpeed * dt;

    m_Yaw -= dYaw;
    m_Pitch -= dPitch;
    if (m_Yaw > 2.0f * M_PI) {
        m_Yaw -= 2.0f * M_PI;
    }

    if (m_Yaw < 0.0f) {
        m_Yaw += 2.0f * M_PI;
    }

    if(m_Pitch > M_PI / 2.0f - 1e-4f) {
        m_Pitch = M_PI / 2.0f - 1e-4f;
    }
    if(m_Pitch < -M_PI / 2.0f + 1e-4f) {
        m_Pitch = -M_PI / 2.0f + 1e-4f;
    }
    updateVectors();
}

void
OrbitalCamera::Zoom(float dy, float dt)  {
    dy *= m_ZoomSpeed * dt;
    m_Radius -= dy;
    if (m_Radius <= 0.5f) {
        m_Radius = 0.5f;
    }

    updateVectors();
}

void
OrbitalCamera::updateVectors() {
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void OrbitalCamera::CalculateDirection(float& xoffset, float& yoffset)
{
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    m_Yaw += xoffset;
    m_Pitch += yoffset;
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(direction);
    updateVectors();
}

void OrbitalCamera::CalculateMoveDirection(std::map<unsigned int, bool>& pressedKeys, float delta)
{
    glm::vec3 dirVector_front = glm::vec3(0);
    glm::vec3 dirVector_side = glm::vec3(0);
    if (pressedKeys[GLFW_KEY_W])
    {
        dirVector_front = glm::normalize(m_Front);
    }
    if (pressedKeys[GLFW_KEY_S])
    {
        dirVector_front = -glm::normalize(m_Front);
    }
    if (pressedKeys[GLFW_KEY_D])
    {
        dirVector_side = glm::normalize(glm::cross(m_Front, m_Up));
    }
    if (pressedKeys[GLFW_KEY_A])
    {
        dirVector_side = -glm::normalize(glm::cross(m_Front, m_Up));
    }
    glm::vec3 direction;
    if (dirVector_front != glm::vec3(0) || dirVector_side != glm::vec3(0))
    {
       direction = glm::normalize(dirVector_front + dirVector_side);    
    }
    m_Position += delta * m_Velocity * direction;
}