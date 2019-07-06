/*
    To Do List:
    * need to figure out how to solve the overlapping problem.
        * implement an array or vector containing all meshes, then loop through structure printing objects with highest z values
        * need a way to find a Vertexes current z values then compare them to find the greatest

*/

#include <iostream>
#include <GL/glew.h>
#include <algorithm>
#include <vector>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "transform.h"


int main(){

    Display dpy(800, 800, "Test Window");
    
    // front
    Shader blueSide("./shaders/blueWall");
    Vertex vertices1[] = { Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),};
    Mesh side1(vertices1, sizeof(vertices1)/sizeof(vertices1[0]));

    // back
    Shader greenSide("./shaders/greenWall");
    Vertex vertices2[] = { Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),};
    Mesh side2(vertices2, sizeof(vertices2)/sizeof(vertices2[0]));



    // top
    Shader orangeSide("./shaders/orangeWall");
    Vertex vertices3[] = { Vertex( glm::vec3(0.25, 0.25, 0.5) ), 
                          Vertex( glm::vec3(-0.25, 0.25, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.25, -0.25, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),};
    Mesh side3(vertices3, sizeof(vertices3)/sizeof(vertices3[0]));

    // bottom
    Shader purpleSide("./shaders/purpleWall");
    Vertex vertices4[] = { Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),};
    Mesh side4(vertices4, sizeof(vertices4)/sizeof(vertices4[0]));

    // left
    Shader whiteSide("./shaders/whiteWall");
    Vertex vertices5[] = { Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),};
    Mesh side5(vertices5, sizeof(vertices5)/sizeof(vertices5[0]));

    // right
    Shader yellowSide("./shaders/floor_shader");
    Vertex vertices6[] = { Vertex( glm::vec3(0.25, 0.25, 0.5) ), 
                          Vertex( glm::vec3(-0.25, 0.25, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.25, -0.25, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),};
    Mesh side6(vertices6, sizeof(vertices6)/sizeof(vertices6[0]));
    



    // instantiate the transform class with our transformations
    Transform transform;
    dpy.GetTransform(&transform);



    // vector of Mesh* for sorting into Draw() order
    std::vector<Mesh*> meshes {&side1, &side2};



    while (!dpy.IsClosed()) {
        dpy.Clear(0.0f, 0.2f, 0.7f, 1.0f);

        /*
        // print z coordinate for testing
        for (int i=0; i < mesh1.GetDrawCount(); i++) 
        {
            std::cout << (mesh1.GetVert()+i)->GetPosZ() << ", ";
        }
        std::cout << "\n";
        */


        // my meshes print in reverse order of being called, the last is top regardless of depth
        whiteSide.Bind();
        blueSide.Update(transform);
        side1.Draw();

        yellowSide.Bind();
        greenSide.Update(transform);
        side2.Draw();





        dpy.Update();
    }

    return 0;
}