#include "camera.h"

namespace GFXREN {

    CAMERA::CAMERA(unsigned int wndW, unsigned int wndH, glm::vec3 position)
        :
        _cameraPosVec(position),
        _worldUpVec(glm::vec3(0.0f, 1.0f, 0.0f)),
        _cameraFrontVec(glm::vec3(0.0f, 0.0f, -1.0f)),
        _yawVal(-90.0f),
        _pitchVal(0.0f),
        _speedVal(2.5f),
        _zoomVal(45.0f),
        _frustumNearPlane(0.1f),
        _frustumFarPlane(300.0f),
        _wndW(wndW),
        _wndH(wndH)
    {
        
        update_vectors();
    }

    void CAMERA::update(const GFXREN::SHADER& shader) {
        
        shader.use();

        update_vectors();
        shader.set_mat4("projection", get_projection_matrix());
        shader.set_mat4("view", get_view_matrix());

    }

    void CAMERA::move(int direction) {

        switch (direction) {

            case CAM_DIR_FORWARD: _cameraPosVec += _cameraFrontVec * _speedVal;
                break;

            case CAM_DIR_BACKWARD: _cameraPosVec -= _cameraFrontVec * _speedVal;
                break;

            case CAM_DIR_RIGHT: _cameraPosVec += _cameraRightVec * _speedVal;
                break;

            case CAM_DIR_LEFT: _cameraPosVec -= _cameraRightVec * _speedVal;
                break;

            case CAM_DIR_UP: _cameraPosVec += _cameraUpVec * _speedVal;
                break;

            case CAM_DIR_DOWN: _cameraPosVec -= _cameraUpVec * _speedVal;
                break;

        }

    }

    void CAMERA::move_forward() { 
        
        _cameraPosVec += _cameraFrontVec * _speedVal; 
    }

    void CAMERA::move_backward() { 
        
        _cameraPosVec -= _cameraFrontVec * _speedVal; 
    }

    void CAMERA::move_right() { 
        
        _cameraPosVec += _cameraRightVec * _speedVal; 
    }

    void CAMERA::move_left() { 
        
        _cameraPosVec -= _cameraRightVec * _speedVal; 
    }

    void CAMERA::move_up() { 
        _cameraPosVec += _cameraUpVec * _speedVal; 
    }

    void CAMERA::move_down() { 
        
        _cameraPosVec -= _cameraUpVec * _speedVal; 
    }

    void CAMERA::look_at(float dx, float dy) {
    
        _yawVal += dx;
        _pitchVal += dy;

        if (_pitchVal > 89.0f) { _pitchVal = 89.0f; }
        else if (_pitchVal < -89.0f) { _pitchVal = -89.0f; }
        
    }

    void CAMERA::zoom(float dy) {

        if (_zoomVal >= 1.0f && _zoomVal <= 45.0f) { _zoomVal -= dy; }
        else if (_zoomVal < 1.0f) { _zoomVal = 1.0f; }
        else { _zoomVal = 45.0f; }
        
    }
    
    void CAMERA::set_yaw(float yaw) {

        _yawVal = yaw;
    }

    void CAMERA::set_pitch(float pitch) {

        _pitchVal = pitch;
    }

    void CAMERA::set_zoom(float zoom) {
        
        _zoomVal = zoom;
    }

    void CAMERA::set_speed(float value, double deltaTime) { 
        
        _speedVal = float(deltaTime * value); 
    }

    float CAMERA::get_yaw() const { 
        
        return _yawVal; 
    }

    float CAMERA::get_pitch() const { 
        
        return _pitchVal; 
    }

    float CAMERA::get_zoom() const { 
        
        return _zoomVal; 
    }

    float CAMERA::get_speed() const {

        return _speedVal;
    }

    glm::vec3 CAMERA::get_position() const {

        return _cameraPosVec;
    }

    glm::mat4 CAMERA::get_view_matrix() const { 
        
        return glm::lookAt(_cameraPosVec, _cameraPosVec + _cameraFrontVec, _cameraUpVec); 
    }

    glm::mat4 CAMERA::get_projection_matrix() const {

        return glm::perspective(glm::radians(_zoomVal), (float)_wndW / (float)_wndH, _frustumNearPlane, _frustumFarPlane);
    }

    void CAMERA::update_vectors() {

        glm::vec3 direction = { 0.0f, 0.0f, 0.0f };

        direction.x = cos(glm::radians(_yawVal)) * cos(glm::radians(_pitchVal));
        direction.y = sin(glm::radians(_pitchVal));
        direction.z = sin(glm::radians(_yawVal)) * cos(glm::radians(_pitchVal));

        _cameraFrontVec = glm::normalize(direction);
        _cameraRightVec = glm::normalize(glm::cross(_cameraFrontVec, _worldUpVec));
        _cameraUpVec = glm::normalize(glm::cross(_cameraRightVec, _cameraFrontVec));

    }

}