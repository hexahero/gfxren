#include "canvas.h"

namespace GFXREN {

    CANVAS::CANVAS(GFXREN::GLCONTEXT& app, GFXREN::MOUSE& mouse)
        :
        _app(app),
        _mouse(mouse)
    {

        _dataLayoutDescriptor.generate_descriptor_array();
        _dataLayoutDescriptor.bind_descriptor_array();

        _vrtxData.generate_vrtx_buff();
        _vrtxData.bind_vrtx_buff();
        _vrtxData.send_vrtx_data(_vertices);

        _indxData.generate_indx_buff();
        _indxData.bind_indx_buff();
        _indxData.send_indx_data(_indices);

        _dataLayoutDescriptor.describe_shader_attribute(0, 3, sizeof(float) * 3, 0);
        _dataLayoutDescriptor.unbind_descriptor_array();

        mouse.show_cursor();

    }

    void CANVAS::update(GFXREN::SHADER& shader) {

        _mouse.cursor_update();

        shader.set_float("time", static_cast<float>(_app.get_currentFrameTime()));
        shader.set_vec2("screenRes", _app.get_screen_resolution());
        shader.set_vec2("mousePos", _mouse.get_mouse_xy());

    }

    void CANVAS::draw() {

        _dataLayoutDescriptor.bind_descriptor_array();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(sizeof(_indices)), GL_UNSIGNED_INT, 0);

    }

}