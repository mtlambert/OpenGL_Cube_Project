#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
// this library below is the GL Math library and will be used in our Vertex class
#include <glm/glm.hpp>




// this class is a supporting class used to get/organize the data we will use to draw in our main class
// in our use here it could be a struct, but far down the line in complexity you may want to add funtions here
// * The way OpenGL organizes 3D data is by using:
//  #1: x, y, and z coordinates between -1 and 1 (vertexes);
//  #2: then taking 3 of those sets to form a triangle (the most basic shape);
class Vertex {
// vertexes are those groupings of 3 numbers; an x, y, and z coordinates between -1 and 1
public:
    // the constructor takes in a reference to a glm::vec3 and saves it as pos for this obj
    Vertex(const glm::vec3 pos) {
        this->pos = pos;
    }

private:
    // below are called vertex attributes, they are set characteristics for a vertex and need to be enabled before using
    glm::vec3 pos;
};




// this class is our main class, it will be used to draw into our window
class Mesh {
public: 
    // constructor takes in a pointer to a class object of the Vertex class and an int representing 
    // the total number of vertecies in our mesh
    Mesh(Vertex* vertices, unsigned int numVertices);
    virtual ~Mesh();

    void Draw();

private:
    // enum that will used to remember NUM_BUFFERS value, I need to look more into enums to understand this
    enum {
        POSITION_VB,

        NUM_BUFFERS
    };
    
    // remeber a GLuint is a basic unit in OpenGL, and this name is the standard way to refer to mesh data on the GPU
    // be aware this is a new feature of OpenGL 3.0, may not work on all versions of OpenGL
    GLuint m_vertexArrayObject;
    // this GLuint represents an array used 
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    // tells OpenGL how much of the m_vertexArrayObject we want to draw
    unsigned int m_drawCount; 

};


#endif