#include "modelbase.h"

namespace GFXREN {

    MODELBASE::MODELBASE()
        :
        _totalVertexCount { 0 },
        _totalIndexCount { 0 }
    {}

    MODELBASE::MODELBASE(const std::string& path)
        :
        _totalVertexCount { 0 },
        _totalIndexCount { 0 }
    {
        
        GFXREN::ASSETLOADER assetLoader;

        // Load model
        assetLoader.load_model(path, &_meshes, &_textures);

        // Retrieve general model data
        for (const auto& mesh : _meshes) {

            _totalVertexCount += mesh.get_vertex_count();
            _totalIndexCount += mesh.get_index_count();

        }
        
    }

    MODELBASE::MODELBASE(MODELBASE&& modelbase) noexcept
        :
        _meshes(std::move(modelbase._meshes)),
        _textures(std::move(modelbase._textures))
    {

        _totalVertexCount = modelbase._totalVertexCount;
        _totalIndexCount = modelbase._totalIndexCount;

        modelbase._meshes.clear();
        modelbase._textures.clear();

        modelbase.~MODELBASE();

    }

    MODELBASE& MODELBASE::operator = (MODELBASE&& modelbase) noexcept {

        if (this != &modelbase) {

            _meshes = std::move(modelbase._meshes);
            _textures = std::move(modelbase._textures);

            _totalVertexCount = modelbase._totalVertexCount;
            _totalIndexCount = modelbase._totalIndexCount;

            modelbase._meshes.clear();
            modelbase._textures.clear();

            modelbase.~MODELBASE();

        }

        return *this;
    }

    void MODELBASE::draw(GFXREN::SHADER& shader) {

        // Engage model meshes and draw them
        for (auto& mesh : _meshes) {

            // Prepare model data for drawing (bind textures, VAOs, etc.)
            mesh.engage(shader);

            // Make draw call
            mesh.draw();

        }

    }

}