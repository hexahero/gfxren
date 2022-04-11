#include "camera.h"

namespace GFXREN {

    CAMERA::CAMERA(unsigned int wndW, unsigned int wndH, glm::vec3 position)
        :
        cameraPosVec(position),
        worldUpVec(glm::vec3(0.0f, 1.0f, 0.0f)),
        cameraFrontVec(glm::vec3(0.0f, 0.0f, -1.0f)),
        yawVal(-90.f),
        pitchVal(0.0f),
        speedVal(2.5f),
        zoomVal(45.0f),
        wndW(wndW),
        wndH(wndH)
    {
        
        update_vectors();
    }

    void CAMERA::update(GFXREN::SHADER& shader) {
        
        update_vectors();
        
        shader.set_mat4("projection", projection);
        shader.set_mat4("view", get_viewMatrix());

    }

    void CAMERA::move(int direction) {

        switch (direction) {

            case CAM_DIR_FORWARD: cameraPosVec += cameraFrontVec * speedVal;
                break;

            case CAM_DIR_BACKWARD: cameraPosVec -= cameraFrontVec * speedVal;
                break;

            case CAM_DIR_RIGHT: cameraPosVec += cameraRightVec * speedVal;
                break;

            case CAM_DIR_LEFT: cameraPosVec -= cameraRightVec * speedVal;
                break;

            case CAM_DIR_UP: cameraPosVec += cameraUpVec * speedVal;
                break;

            case CAM_DIR_DOWN: cameraPosVec -= cameraUpVec * speedVal;
                break;

        }

    }

    void CAMERA::move_forward() { 
        
        cameraPosVec += cameraFrontVec * speedVal; 
    }

    void CAMERA::move_backward() { 
        
        cameraPosVec -= cameraFrontVec * speedVal; 
    }

    void CAMERA::move_right() { 
        
        cameraPosVec += cameraRightVec * speedVal; 
    }

    void CAMERA::move_left() { 
        
        cameraPosVec -= cameraRightVec * speedVal; 
    }

    void CAMERA::move_up() { 
        cameraPosVec += cameraUpVec * speedVal; 
    }

    void CAMERA::move_down() { 
        
        cameraPosVec -= cameraUpVec * speedVal; 
    }

    void CAMERA::look_at(float dx, float dy) {
    
        yawVal += dx;
        pitchVal += dy;

        if (pitchVal > 89.0f) { pitchVal = 89.0f; }
        else if (pitchVal < -89.0f) { pitchVal = -89.0f; }
        
    }

    void CAMERA::zoom(float dy) {

        if (zoomVal >= 1.0f && zoomVal <= 45.0f) { zoomVal -= dy; }
        else if (zoomVal < 1.0f) { zoomVal = 1.0f; }
        else { zoomVal = 45.0f; }
        
    }
    
    void CAMERA::set_speed(float value, double deltaTime) { 
        
        speedVal = float(deltaTime * value); 
    }

    float CAMERA::get_yaw() const { 
        
        return yawVal; 
    }

    float CAMERA::get_pitch() const { 
        
        return pitchVal; 
    }

    float CAMERA::get_speed() const { 
        
        return speedVal; 
    }

    float CAMERA::get_zoom() const { 
        
        return zoomVal; 
    }

    glm::mat4 CAMERA::get_viewMatrix() const { 
        
        return glm::lookAt(cameraPosVec, cameraPosVec + cameraFrontVec, cameraUpVec); 
    }

    void CAMERA::update_vectors() {

        glm::vec3 direction;

        direction.x = cos(glm::radians(yawVal)) * cos(glm::radians(pitchVal));
        direction.y = sin(glm::radians(pitchVal));
        direction.z = sin(glm::radians(yawVal)) * cos(glm::radians(pitchVal));

        cameraFrontVec = glm::normalize(direction);
        cameraRightVec = glm::normalize(glm::cross(cameraFrontVec, worldUpVec));
        cameraUpVec = glm::normalize(glm::cross(cameraRightVec, cameraFrontVec));

        projection = glm::perspective(glm::radians(zoomVal), (float)wndW / (float)wndH, 0.1f, 300.0f);

    }

}