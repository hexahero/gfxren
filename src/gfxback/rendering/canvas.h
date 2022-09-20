#pragma once

#include "../gpudata/layouter.h"
#include "../gpudata/vrtxdata.h"
#include "../gpudata/indxdata.h"

#include "../shader/shader.h"

#include "../context/glctx.h"
#include "../input/msinput.h"

namespace GFXREN {

    class CANVAS {

    public:

        CANVAS() = delete;
        CANVAS(const CANVAS&) = delete;

        CANVAS(GFXREN::GLCONTEXT& app, GFXREN::MOUSE& mouse);

        void update(GFXREN::SHADER& shader);
        void draw();

    private:

        std::vector<float>          _vertices {
             1.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f
        };
        std::vector<unsigned int>   _indices {
            0, 1, 3,
            1, 2, 3
        };

        GFXREN::LAYOUTER _dataLayoutDescriptor;
        GFXREN::VRTXDATA _vrtxData;
        GFXREN::INDXDATA _indxData;

        GFXREN::GLCONTEXT&  _app;
        GFXREN::MOUSE&      _mouse;

    };

}