/*
    TO DO LIST:

    * Enabling GL_DEPTH_TEST, configuring glDepthFunc() to GL_LESS, and clearing the GL_BUFFER_DEPTH_BIT solved my oerlapping prooblem
       but i'm not entirely sure how it did it....

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
    Vertex vertices3[] = { Vertex( glm::vec3(-0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ),
                          Vertex( glm::vec3(0.5, 0.5, 0.5) ),};
    Mesh side3(vertices3, sizeof(vertices3)/sizeof(vertices3[0]));

    // bottom
    Shader purpleSide("./shaders/purpleWall");
    Vertex vertices4[] = { Vertex( glm::vec3(-0.5, -0.5, 0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),
                        
                          Vertex( glm::vec3(0.5, -0.5, -0.5) ), 
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),};
    Mesh side4(vertices4, sizeof(vertices4)/sizeof(vertices4[0]));

    // left
    Shader whiteSide("./shaders/whiteWall");
    Vertex vertices5[] = { Vertex( glm::vec3(-0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(-0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(-0.5, -0.5, -0.5) ),
                          Vertex( glm::vec3(-0.5, -0.5, 0.5) ),};
    Mesh side5(vertices5, sizeof(vertices5)/sizeof(vertices5[0]));

    // right
    Shader yellowSide("./shaders/floor_shader");
    Vertex vertices6[] = {Vertex( glm::vec3(0.5, 0.5, 0.5) ), 
                          Vertex( glm::vec3(0.5, 0.5, -0.5) ),
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),
                        
                          Vertex( glm::vec3(0.5, 0.5, -0.5) ), 
                          Vertex( glm::vec3(0.5, -0.5, -0.5) ),
                          Vertex( glm::vec3(0.5, -0.5, 0.5) ),};
    Mesh side6(vertices6, sizeof(vertices6)/sizeof(vertices6[0]));
    



    // instantiate the transform class with our transformations
    Transform transform;
    dpy.SetTransform(&transform);


    while (!dpy.IsClosed()) {
        dpy.Clear(0.0f, 0.0f, 0.0f, 1.0f);

        // below solved the draw overlapping problem.....
        // why....   I'm not entirely sure
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS); 

        /*
        // print z coordinate for testing
        for (int i=0; i < side1.GetDrawCount(); i++) 
        {
            std::cout << (side1.GetVert()+i)->GetPosZ() << ", ";
        }
        std::cout << "\n";
        */
        //std::cout << transform.GetPos()[2] << "\n";
        

        // my meshes print in reverse order of being called, the last is top regardless of depth
        greenSide.Bind();
        greenSide.Update(transform);
        side2.Draw();

        orangeSide.Bind();
        orangeSide.Update(transform);
        side3.Draw();

        blueSide.Bind();
        blueSide.Update(transform);
        side1.Draw();

        purpleSide.Bind();
        purpleSide.Update(transform);
        side4.Draw();

        //whiteSide.Bind();
        //whiteSide.Update(transform);
        //side5.Draw();

        yellowSide.Bind();
        yellowSide.Update(transform);
        side6.Draw();

        dpy.Update();
    }

    return 0;
}