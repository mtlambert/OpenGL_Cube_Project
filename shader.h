#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include "transform.h"

class Shader {
public:
    Shader(const std::string fileName);
    void Bind();
    // used to do our transformation, by modifying the values in our array
    void Update(const Transform& transform);
    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2;
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];

    // additions below for Transform class
    enum {
        // transformation uniforms
        TRANSFORM_U_,
        // the number of unifroms to keep track of
        NUM_UNIFORMS
    };
    // we will refere to our uniform variables in an array
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif