/**
 * @file camera.hpp
 * @author Jovan Ivosevic
 * @brief First Person Camera
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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

    /**
     * @brief Ctor
     *
     * @param fov - Vertical Field of View
     * @param distance - Camera distance from target
     * @param rotateSpeed - Camera rotation speed
     * @param zoomSpeed - Zoom speed
     * @param worldUp - World Up vector
     * @param target - Point in space the camera's looking at
     */
    OrbitalCamera(float fov, glm::vec3 position, float distance, float rotateSpeed = 10.0f, float zoomSpeed = 10.0f, const glm::vec3 &worldUp = glm::vec3(0.0f, 1.0f, 0.0f), const glm::vec3 &target = glm::vec3(0.0f));

    /**
     * @brief Rotates the camera
     *
     * @param dYaw - How much the camera rotates around the Up vector. Delta Yaw
     * @param dPitch - How much the camera rotates around the Right vector. Delta Pitch
     * @param dt - Delta time
     */
    void Rotate(float dYaw, float dPitch, float dt);

    /**
     * @brief Moves the camera towards the target
     *
     * @param dy - How much the camera moves towards the target. Delta y
     * @param dt - Delta time
     */
    void Zoom(float dy, float dt);
    void CalculateDirection(float& xoffset, float& yoffset);
    void CalculateMoveDirection(std::map<unsigned int, bool>& pressedKeys, float delt);

private:

    /**
     * @brief Called after Rotating, Zooming, etc... Updates all the camera vectors accordingly
     *
     */
    void updateVectors();
};