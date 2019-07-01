#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>

class Shader {
public:
    // shaders are actually written in seperate files, so the constructor will take that files name
    Shader(const std::string fileName);

    // this function binds this shader class to a program and if a shader class is
    // already applied to the program this function will replace it with the current class 
    void Bind();

    virtual ~Shader();

private:
    // sets the number of shaders for the program, 2 works in this case.
    // "if working with geometry may want 3""
    static const unsigned int NUM_SHADERS = 2;
    
    // GLuint are means with which GL "keeps track of a program"
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};

#endif