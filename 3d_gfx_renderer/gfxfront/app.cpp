/*

TODO:

make Exceptions class actually throw exceptions xddd
deal with shader linkage incorrect exception
handle call errors in modules

*/

#include <iostream>
#include <vector>
#include <gfxren.h>

unsigned int SCR_X = 550;
unsigned int SCR_Y = 230;

unsigned int SCR_W = 1280;
unsigned int SCR_H = 720;

bool wireframeMode = false;
bool textured = true;

int cameraMode = CAM_TYPE_FLYCAM;

GFXREN::GLCONTEXT app(
                        "GFXREN DEMO (OpenGL) ", 
                        "../resources/ico/cog_small.png", 
                        SCR_X, 
                        SCR_Y, 
                        SCR_W, 
                        SCR_H, 
                        true, 
                        true
                     );
GFXREN::RENDERER renderer;
GFXREN::CAMERA camera(SCR_W, SCR_H, { 0.0f, 1.5f, 7.0f });
GFXREN::KEYBOARD keyboard(app.get_window_handle());
GFXREN::MOUSE mouse(app.get_window_handle());
GFXREN::LOGGER<const char*> logger;

std::vector<float> refPlaneVerts{

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f

};
std::vector<float> cubeVerts{

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                              
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                              
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                              
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                              
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                              
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

};

GFXREN::SHADER shaderBasic(DEFAULT_DIR"basic_vrtx.glsl", DEFAULT_DIR"basic_pxl.glsl");

GFXREN::MODEL refplane(
    "Reference plane (30, 0, 30)",
    "../resources/textures/checkerboard_grey_hr.png",
    { 0.0f, 0.0f, 0.0f },
    refPlaneVerts
);

GFXREN::MODEL cube1(
    "Cube1",
    "../resources/textures/checkerboard_green1.png",
    { 0.0f, 1.0f, 0.0f },
    cubeVerts
);

GFXREN::MODEL cube2(
    "Cube2",
    "../resources/textures/checkerboard_green2.png",
    { 2.5f, 1.9f, -3.0f },
    cubeVerts
);

GFXREN::MODEL cube3(
    "Cube3",
    "../resources/textures/checkerboard_green2.png",
    { -3.0f, 1.0f, -2.0f },
    cubeVerts
);

void bind_keys() {

    keyboard.on_key_press(GFXREN_KEY_M, []() {

        if (wireframeMode == true) {

            if (cameraMode == CAM_TYPE_FLYCAM) cameraMode = CAM_TYPE_FLYCAM_MS;
            else cameraMode = CAM_TYPE_FLYCAM;

            wireframeMode = false;
            mouse.lock_cursor();

            logger.clog("Wireframe mode disabled", LERROR);

        }
        else {

            if (cameraMode == 1) cameraMode = 2;
            else cameraMode = 1;

            wireframeMode = true;
            mouse.show_cursor();

            logger.clog("Wireframe mode enabled", LSUCCESS);

        }

    });

    keyboard.on_key_press(GFXREN_KEY_F, []() {

        app.enable_full_screen();
    });

    keyboard.on_key_press(GFXREN_KEY_T, []() {

        if (textured) {

            textured = false;
            cube3.scale(2.0f, 2.0f, 2.0f);

        }
        else {

            textured = true;
            cube3.scale(-2.0f, -2.0f, -2.0f);

        }

    });

    keyboard.on_key_press(GFXREN_KEY_I, []() {

        app.print_system_info();
    });

    mouse.on_button_press(GFXREN_MBR, []() {

        logger.clog("EVENT> mouse button \"Right\" pressed");
    });

}

void process_input() {

    if (keyboard.press(GFXREN_KEY_W)) {
        
        camera.move_forward();
        logger.clog("EVENT> key \"W\" pressed");

    }
    if (keyboard.press(GFXREN_KEY_A)) {

        camera.move_left();
        logger.clog("EVENT> key \"A\" pressed");

    }
    if (keyboard.press(GFXREN_KEY_S)) {

        camera.move_backward();
        logger.clog("EVENT> key \"S\" pressed");

    }
    if (keyboard.press(GFXREN_KEY_D)) {

        camera.move_right();
        logger.clog("EVENT> key \"D\" pressed");

    }
    if (keyboard.press(GFXREN_KEY_SPACEBAR)) {

        camera.move_up();
        logger.clog("EVENT> key \"SPACE_BAR\" pressed");

    }
    if (mouse.scroll()) {

        float scrollDy = float(mouse.get_mouse_scrollDy());

        if (scrollDy != 0) camera.zoom(scrollDy);
        logger.clog("EVENT> mouse scroll");

    }

    float dx = float(mouse.get_mouse_dx());
    float dy = float(mouse.get_mouse_dy());

    if (cameraMode == CAM_TYPE_FLYCAM) {

        if (dx != 0 || dy != 0) camera.look_at(dx / 5, dy / 5);

    }
    else {

        if (mouse.press(GFXREN_MBL)) {

            if (dx != 0 || dy != 0) camera.look_at(dx / 4, dy / 4);
        }

    }

    mouse.cursor_update();

}

void setup() {

    bind_keys();

    refplane.scale(30.0f, 0.0f, 30.0f);
    cube1.scale(2.0f, 2.0f, 2.0f);
    cube2.scale(2.0f, 2.0f, 2.0f);
    cube3.scale(2.0f, 2.0f, 2.0f);

}

void update_frame() {

    renderer.clear(GFXREN_BLACK);
    process_input();

    cube2.rotate(0.7f, { 0.5f, 0.5f, 0.5f });
    cube2.move(0.0f, 0.002f, 0.0f);
    cube3.move(-0.002f, 0.0f, 0.0f);

    camera.set_speed(10.0f, app.get_deltaTime());
    camera.update(shaderBasic);

    renderer.draw_model(refplane, shaderBasic, wireframeMode);
    renderer.draw_model(cube1, shaderBasic, wireframeMode, textured);
    renderer.draw_model(cube2, shaderBasic, wireframeMode, textured);
    renderer.draw_model(cube3, shaderBasic, wireframeMode, textured);

    app.show_fps_and_mspos("GFXREN DEMO (OpenGL) ", mouse);

}

int main() {

    setup();
    app.run(update_frame);

    return 0;
}