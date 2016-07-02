//
// Created by Максим Фалалеев on 27/06/16.
//

#include "Shader.h"

namespace fastcraft {

    Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
        // 1. Retrieve the vertex/fragment source code from filePath

        std::string vertexCode = File::open(vertexPath);
        std::string fragmentCode = File::open(fragmentPath);
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();

        // 2. Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // Print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Shader Program
        _program = glCreateProgram();
        glAttachShader(_program, vertex);
        glAttachShader(_program, fragment);
        glLinkProgram(_program);
        // Print linking errors if any
        glGetProgramiv(_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    GLuint Shader::getProgramId() {
        return _program;
    }

    GLint Shader::getUniform(const GLchar *name) {
        GLint result = glGetUniformLocation(_program, name);
        if (result == -1) std::cerr << "Could not find location for '" << name << "'" << std::endl;
        return result;
    }

    void Shader::setUniformMatrix(const char *name, glm::mat4 matrix) {
        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setUniformInt(const char *name, GLuint data) {
        glUniform1i(getUniform(name), data);
    }

    void Shader::setUniformFloat1(const char *name, float data) {
        glUniform1f(getUniform(name), data);
    }

    void Shader::setUniformFloat2(const char *name, glm::vec2 data) {
        glUniform2f(getUniform(name), data.x, data.y);
    }

    void Shader::setUniformFloat3(const char *name, glm::vec3 data) {
        glUniform3f(getUniform(name), data.x, data.y, data.z);
    }

    void Shader::setUniformFloat4(const char *name, glm::vec4 data) {
        glUniform4f(getUniform(name), data.x, data.y, data.z, data.w);
    }

    void Shader::enable() {
        glUseProgram(_program);
    }

    void Shader::disable() {
        glUseProgram(0);
    }

    GLint Shader::attrib(const GLchar *attribName) const {
        if (!attribName) {
            throw std::runtime_error("attribName was NULL");
        }

        GLint attrib = glGetAttribLocation(_program, attribName);
        if (attrib == -1) {
            throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
        }

        return attrib;
    }

}