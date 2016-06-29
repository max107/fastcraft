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

namespace fastcraft {

    class Shader {
    public:
        // Constructor generates the shader on the fly
        Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

        // Uses the current shader
        void use();

        GLuint getProgramId();

    private:
        GLuint _program;
    };

}

#endif //FASTCRAFT_SHADER_H
