#ifndef LEARN_OPENGL_CAMERA_H_LF
#define LEARN_OPENGL_CAMERA_H_LF
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace gll{


// Default camera values
const float YAW         = -90.0f;   // rotate by y-axis
const float PITCH       = 0.0f;     // rotate by x-axis
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1;
const float ZOOM        = 45.0f;

/**
 * @brief An abstract camera class that processes input and calculates the 
 * corresponding Euler Angles, Vectors and Matrices for use in OpenGL.
 * 
 */
class Camera
{
public:
    /** 
     * @brief Defines several possible options for camera movement. Used as 
     * abstraction to stay away from window-system specific input methods
     */
    enum Movement
    {
        MOVE_FORWARD,
        MOVE_BACKWARD,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN
    };

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        : front(glm::vec3(0.0f, 0.0f, -1.0f))
        , move_speed(SPEED)
        , mouse_sensitivity(SENSITIVITY)
        , zoom(ZOOM)
    {
        this->position = position;
        this->world_up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
        : front(glm::vec3(0.0f, 0.0f, -1.0f))
        , move_speed(SPEED)
        , mouse_sensitivity(SENSITIVITY)
        , zoom(ZOOM)
    {
        this->position = glm::vec3(pos_x, pos_y, pos_z);
        this->world_up = glm::vec3(up_x, up_y, up_z);
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    /**
     * @brief Get the View Matrix calculated using Euler Angles
     * 
     * @return glm::mat4 
     */
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    void processKeyboard(Movement direction, float delta_time)
    {
        float velocity = move_speed * delta_time;
        switch (direction)
        {
        case MOVE_FORWARD:
            position += front * velocity;
            break;
        case MOVE_BACKWARD:
            position -= front * velocity;
            break;
        case MOVE_LEFT:
            position -= right * velocity;
            break;
        case MOVE_RIGHT:
            position += right * velocity;
            break;
        case MOVE_UP:
            position += up * velocity;
            break;
        case MOVE_DOWN:
            position -= up * velocity;
            break;
        default:
            break;
        }
    }

    void processMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true)
    {
        x_offset *= mouse_sensitivity;
        y_offset *= mouse_sensitivity;

        yaw += x_offset;
        pitch += y_offset;

        if(constrain_pitch){
            if(pitch > 89.0f) pitch = 89.0f;
            if(pitch < -89.0f) pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void processMouseScroll(float y_offset)
    {
        zoom -= static_cast<float>(y_offset);
        if(zoom < 1.0f) zoom = 1.0f;
        if(zoom > 45.0f) zoom = 45.0f;
    }

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    // Euler angles
    float yaw;
    float pitch;
    // Camera options
    float move_speed;
    float mouse_sensitivity;
    float zoom;
private:
    void updateCameraVectors()
    {
        // Calculate the new front vector
        glm::vec3 forward;
        forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward.y = sin(glm::radians(pitch));
        forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(forward);
        // Update right and up
        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));
    }
};

} // namespace::gll
#endif // LEARN_OPENGL_CAMERA_H_LF