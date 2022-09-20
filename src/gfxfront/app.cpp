#include "app.h"

#ifdef SHADER_DRAW

void update_frame() {

    renderer.clear(GFXREN_BLACK);

    //renderer.draw_shader_canvas(canvas, sandboxShaderCircle);
    //renderer.draw_shader_canvas(canvas, sandboxShaderRect);
    //renderer.draw_shader_canvas(canvas, shaderNoise);
    renderer.draw_shader_canvas(canvas, shaderCubeLines);

    app.show_fps_and_mspos("GFXREN DEMO (OpenGL) ", mouse);

}

int main() {

    app.run(update_frame);

    return 0;
}

#else

void bind_keys() {

    keyboard.on_key_press(GFXREN_KEY_G, []() {

        if (guiEnabled == true) {

            guiEnabled = false;
            logger.clog("GUI disabled", LERROR);

        }
        else {

            guiEnabled = true;
            logger.clog("GUI enabled", LSUCCESS);

        }

    });

    keyboard.on_key_press(GFXREN_KEY_F, []() {

        if (!app.is_fullscreen()) {

            guiEnabled = false;
            app.enable_full_screen();

        }
        else {

            guiEnabled = true;
            app.disable_full_screen();

        }
        
    });

    keyboard.on_key_press(GFXREN_KEY_I, []() {

        app.print_system_info();
    });

    mouse.on_button_press(GFXREN_MBR, []() {

        if (mouse.is_cursor_hidden()) {

            cameraMode = CAM_TYPE_FLYCAM_MS;
            mouse.toggle_cursor();

        }
        else {

            cameraMode = CAM_TYPE_FLYCAM;
            mouse.toggle_cursor();

        }

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
    camera.set_pitch(-30.0f);

    gui.register_action("enable_face_culling",      [=]() { app.enable_face_culling(); });
    gui.register_action("disable_face_culling",     [=]() { app.disable_face_culling(); });
    gui.register_action("enable_wireframe_mode",    [=]() { wireframeMode = true; });
    gui.register_action("disable_wireframe_mode",   [=]() { wireframeMode = false; });
    gui.register_action("enable_textures",          [=]() { textured = true; });
    gui.register_action("disable_textures",         [=]() { textured = false; });

    refgrid.set_scale(10.0f, 10.0f, 10.0f);
    lightsource.set_scale(0.5f, 0.5f, 0.5f);

}

void update_frame() {
    

    renderer.clear(clearColour);
    
    // Temp lighting stuff
    lightsourceShader.use();
    lightsourceShader.set_vec4("lightColor", { 1.0f, 1.0f, 1.0f, 1.0f });

    basicShader.use();

    basicShader.set_vec3("cameraPos", camera.get_position());
    basicShader.set_vec3("lightPos", { 10.0f, 9.0f, 0.0f });
    basicShader.set_vec4("lightColor", { 1.0f, 1.0f, 1.0f, 1.0f });

    basicShader.set_float("ambientIntensity", 0.5f);
    basicShader.set_float("specularIntensity", 0.5f);

    // Process input
    if (!gui.is_capturing_mouse()) process_input();
    
    // Update scene state
    camera.set_speed(10.0f, app.get_deltaTime());
    camera.update(basicShader);
    camera.update(refgridShader);
    camera.update(lightsourceShader);

    // Update model states
    if (!models.empty()) models[0].rotate(0.7f, { 0.0f, 0.5f, 0.0f });
    
    // Make draw calls

    for (auto& model : models)
        renderer.draw_model(model, basicShader, wireframeMode, textured);

    renderer.draw_model(lightsource, lightsourceShader, false, false);

    if (refgridOn)
        renderer.draw_model(refgrid, refgridShader, false, false);

    // Draw GUI
    if (guiEnabled) gui.draw();

    // Info
    app.show_fps_and_mspos("GFXREN DEMO (OpenGL) ", mouse);

}

int main() {

    setup();
    app.run(update_frame);
    gui.destroy();

    return 0;
}

#endif