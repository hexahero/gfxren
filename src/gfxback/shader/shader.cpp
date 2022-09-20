#include "shader.h"

namespace GFXREN {

    SHADER::SHADER() 
        :
        _shaderProgramID(NULL),
        _compiledVertexShader(NULL),
        _compiledFragmentShader(NULL),
        _compiledGeometryShader(NULL)
    {}

    SHADER::SHADER(const char* vertex, const char* fragment, const char* geometry) {

        add(vertex, fragment, geometry);
    }

    void SHADER::add(const char* vertex, const char* fragment, const char* geometry) {

        build_shader_program(vertex, fragment, geometry);
    }

    unsigned int SHADER::get_id() const { 
        
        return _shaderProgramID; 
    }

    void SHADER::build_shader_program(const char* vertex, const char* fragment, const char* geometry) {

        //Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        //Ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {

            //Open files
            vShaderFile.open(vertex);
            fShaderFile.open(fragment);

            std::stringstream vShaderStream;
            std::stringstream fShaderStream;

            //Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            //Close file handlers
            vShaderFile.close();
            fShaderFile.close();

            //Convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            //If geometry shader path is present, also load a geometry shader
            if (geometry != nullptr) {

                gShaderFile.open(geometry);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();

            }

        }
        catch (std::ifstream::failure&) { 
            
            PRINT_ERROR("SHADER FILE READING FAILURE", true, false); 
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        const char* gShaderCode = nullptr;
        if (geometry != nullptr) { gShaderCode = geometryCode.c_str(); }

        //Build shader program

        compile_vertex_shader(vShaderCode);
        compile_fragment_shader(fShaderCode);
        if (geometry != nullptr) { compile_geometry_shader(gShaderCode); }

        link_shaders();

    }

    unsigned int SHADER::compile_vertex_shader(const char* vShaderCode) {

        //Compile vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);

        //Compile error check
        check_err(vertexShader, "VERTEX");

        _compiledVertexShader = vertexShader;
        return vertexShader;
    }

    unsigned int SHADER::compile_fragment_shader(const char* fShaderCode) {

        //Compile fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);

        //Compile error check
        check_err(fragmentShader, "FRAGMENT");

        _compiledFragmentShader = fragmentShader;
        return fragmentShader;
    }

    unsigned int SHADER::compile_geometry_shader(const char* gShaderCode) {

        //Compile geometry shader
        unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShaderCode, NULL);
        glCompileShader(geometryShader);

        //Compile error check
        check_err(geometryShader, "GEOMETRY");

        _compiledGeometryShader = geometryShader;
        return geometryShader;
    }

    unsigned int SHADER::link_shaders() {

        //Linking shaders
        _shaderProgramID = glCreateProgram();

        glAttachShader(_shaderProgramID, _compiledVertexShader);
        glAttachShader(_shaderProgramID, _compiledFragmentShader);
        if (_compiledGeometryShader != 0) { glAttachShader(_shaderProgramID, _compiledVertexShader); }

        glLinkProgram(_shaderProgramID);

        //Link error check
        check_err(_shaderProgramID, "LINKAGE");

        //Delete linked shaders
        glDetachShader(_shaderProgramID, _compiledVertexShader);
        glDeleteShader(_compiledVertexShader);

        glDetachShader(_shaderProgramID, _compiledFragmentShader);
        glDeleteShader(_compiledFragmentShader);

        if (_compiledGeometryShader != 0) {

            glDetachShader(_shaderProgramID, _compiledGeometryShader);
            glDeleteShader(_compiledFragmentShader);

        }

        return _shaderProgramID;
    }

    unsigned short SHADER::check_err(unsigned int shader, const char* type) {

        int success;
        char infoLog[1024];
        std::ostringstream errmsg;

        if (std::strcmp(type, "LINKAGE") != 0) {

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success) {

                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                errmsg << type << " SHADER COMPILATION FAILED (" << infoLog << ")";
                PRINT_ERROR(errmsg.str().c_str(), true, false);

                return 1;
            }

        }
        else {

            glGetProgramiv(shader, GL_LINK_STATUS, &success);

            if (!success) {

                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                errmsg << "SHADER LINKAGE FAILED (" << infoLog << ")";
                PRINT_ERROR(errmsg.str().c_str(), true, false);

                return 2;
            }

        }

        return 0;
    }

}