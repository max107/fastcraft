//
// Created by Максим Фалалеев on 27/06/16.
//

#ifndef FASTCRAFT_SHADER_H
#define FASTCRAFT_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "File.h"

namespace fastcraft {

    class Shader {
    public:
        // Constructor generates the shader on the fly
        Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

        GLuint getProgramId();

        GLint getUniform(const char *name);

        void setUniformMatrix(const char *name, glm::mat4 matrix);

        void setUniformInt(const char *name, GLuint data);

        void setUniformFloat1(const char *name, float data);

        void setUniformFloat2(const char *name, glm::vec2 data);

        void setUniformFloat3(const char *name, glm::vec3 data);

        void setUniformFloat4(const char *name, glm::vec4 data);

        // Uses the current shader
        void enable();

        void disable();

        GLint attrib(const GLchar* attribName) const;

    private:
        GLuint _program;
    };

}

#endif //FASTCRAFT_SHADER_H
