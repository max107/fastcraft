#ifndef FASTCRAFT_VERTEXARRAY_H
#define FASTCRAFT_VERTEXARRAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace fastcraft {

    class VertexArray {

    public:
        VertexArray(GLfloat *vertices, GLuint *indices,
                    GLfloat *normals, GLfloat *tcs, GLsizei vcount, GLsizei icount);

        void render();

    private:
        GLuint vao, ibo;

        GLfloat *vertices;
        GLuint *indices;
        GLfloat *normals;
        GLfloat *tcs;
        GLsizei vcount;
        GLsizei icount;

        GLuint compile();
    };

}

#endif //FASTCRAFT_VERTEXARRAY_H
