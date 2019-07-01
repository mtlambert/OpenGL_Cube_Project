#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"

int main(){

    Display dpy(800, 600, "title");

    // below we instantiate our shader object, with the file path to its file
    Shader shader("./res/basicShader");

    // instantiating a set of vertexes to draw by creating an array of vertex class objects
    //  that will go into our Mesh class constructor and Mesh class will put into a buffer on the GPU. 
    //  OpenGL coordinates are from -1 to 1, here we ignore the z coordinate since we are drawing 2D
    /* 
               1  1  1       x = 1 means right, x = 0 means middle, x = -1 means left
            -1         1     y = 1 means top, y = 0 means middle, y = -1 means bottom
            -1         1     z = 1 means close, z = 0 means middle, z = -1 means far
            -1         1
              -1 -1 -1       glm::vec3( x, y, z)

    */
    
    Vertex vertices[] = { Vertex( glm::vec3(0, 0, 0) ), 
                          Vertex( glm::vec3(-1,-1, 0) ),
                          Vertex( glm::vec3(-1, 1, 0) ),
                          Vertex( glm::vec3(0, 0, 0) ), 
                          Vertex( glm::vec3(1, 1, 0) ),
                          Vertex( glm::vec3(1, -1, 0) ),};
    

    /*
    Vertex vertices[] = { Vertex( glm::vec3(0, 1, 0) ), 
                          Vertex( glm::vec3(-1, -1, 0) ),
                          Vertex( glm::vec3(1, -1, 0) )};
    */

    // instantiating the Mesh class with our vertices
    //  below we calculate the numVertices by dividing the total size of verticies by the size of a single vertex 
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));



    while (!dpy.IsClosed()) {
        dpy.Clear(0.0f, 0.2f, 0.7f, 1.0f);

        // now that we have our shader class we can bind our shader to shade what we draw
        shader.Bind();
        
        // used to actually draw our vertexes
        mesh.Draw();

        dpy.Update();
    }

    return 0;
}