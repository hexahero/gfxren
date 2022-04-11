#include "shader.h"

namespace GFXREN {

    SHADER::SHADER() 
        :
        shaderProgramID(NULL),
        compiledVertexShader(NULL),
        compiledFragmentShader(NULL),
        compiledGeometryShader(NULL)
    {}

    SHADER::SHADER(const char* vertex, const char* fragment, const char* geometry) {

        add(vertex, fragment, geometry);
    }

    void SHADER::add(const char* vertex, const char* fragment, const char* geometry) {

        build_shader_program(vertex, fragment, geometry);
    }

    unsigned int SHADER::get_id() const { 
        
        return shaderProgramID; 
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
        catch (std::ifstream::failure&) { EXCEPTION("SHADER FILE READING FAILURE", true); }

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

        compiledVertexShader = vertexShader;
        return vertexShader;
    }

    unsigned int SHADER::compile_fragment_shader(const char* fShaderCode) {

        //Compile fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);

        //Compile error check
        check_err(fragmentShader, "FRAGMENT");

        compiledFragmentShader = fragmentShader;
        return fragmentShader;
    }

    unsigned int SHADER::compile_geometry_shader(const char* gShaderCode) {

        //Compile geometry shader
        unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &gShaderCode, NULL);
        glCompileShader(geometryShader);

        //Compile error check
        check_err(geometryShader, "GEOMETRY");

        compiledGeometryShader = geometryShader;
        return geometryShader;
    }

    unsigned int SHADER::link_shaders() {

        //Linking shaders
        shaderProgramID = glCreateProgram();

        glAttachShader(shaderProgramID, compiledVertexShader);
        glAttachShader(shaderProgramID, compiledFragmentShader);
        if (compiledGeometryShader != 0) { glAttachShader(shaderProgramID, compiledVertexShader); }

        glLinkProgram(shaderProgramID);

        //Link error check
        check_err(shaderProgramID, "LINKAGE");

        //Delete linked shaders
        glDetachShader(shaderProgramID, compiledVertexShader);
        glDeleteShader(compiledVertexShader);

        glDetachShader(shaderProgramID, compiledFragmentShader);
        glDeleteShader(compiledFragmentShader);

        if (compiledGeometryShader != 0) {

            glDetachShader(shaderProgramID, compiledGeometryShader);
            glDeleteShader(compiledFragmentShader);

        }

        return shaderProgramID;
    }

    unsigned short SHADER::check_err(unsigned int shader, const char* type) {

        int success;
        char infoLog[1024];
        std::ostringstream errmsg;

        if (type != "LINKAGE") {

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success) {

                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                errmsg << type << " SHADER COMPILATION FAILED (" << infoLog << ")";
                EXCEPTION(errmsg.str().c_str(), false);

                return 1;
            }

        }
        else {

            glGetProgramiv(shader, GL_LINK_STATUS, &success);

            if (!success) {

                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                errmsg << "SHADER LINKAGE FAILED (" << infoLog << ")";
                EXCEPTION(errmsg.str().c_str(), false);

                return 2;
            }

        }

        return 0;
    }

}