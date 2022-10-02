#pragma once

#include <gtc/matrix_transform.hpp>
#include "../shader/shader.h"

#define CAM_TYPE_FLYCAM     1
#define CAM_TYPE_FLYCAM_MS  2

#define CAM_DIR_NONE        0
#define CAM_DIR_FORWARD     1
#define CAM_DIR_BACKWARD    2
#define CAM_DIR_RIGHT       3
#define CAM_DIR_LEFT        4
#define CAM_DIR_UP          5
#define CAM_DIR_DOWN        6

namespace GFXREN {

    class CAMERA {

    public:

        CAMERA(unsigned int wndW, unsigned int wndH, glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));

		void update(double frameDeltaTime);
        void update_shader(const GFXREN::SHADER& shader);

        void move(int direction);
        void move_forward();
        void move_backward();
        void move_right();
        void move_left();
        void move_up();
        void move_down();

        void look_at(float dx, float dy);
        void zoom(float dy);

		void set_frustum_far_plane(const float farPlane);

        void set_yaw(float yaw);
        void set_pitch(float pitch);
        void set_zoom(float zoom);
        void set_speed(float value);
		void set_speed_time(float value);

		float get_frustum_far_plane() const;

        float get_yaw() const;
        float get_pitch() const;
        float get_zoom() const;
        float get_speed() const;
        float get_speed_time() const;

        glm::vec3 get_position() const;

        glm::mat4 get_view_matrix() const;
        glm::mat4 get_projection_matrix() const;

    private:

		void update_vectors();

		float _speed;

        glm::vec3 _cameraPosVec;
        glm::vec3 _worldUpVec;

        glm::vec3 _cameraFrontVec;
        glm::vec3 _cameraUpVec;
        glm::vec3 _cameraRightVec;

        float _yawVal;
        float _pitchVal;
        float _speedTimeVal;
        float _zoomVal;

        float _frustumNearPlane;
        float _frustumFarPlane;

        unsigned int _wndW;
        unsigned int _wndH;

    };

}