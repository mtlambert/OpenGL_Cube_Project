#include "mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
    // set m_drawCount, the amount of our m_vertexArrayObject, to the value we passed in as numVerticies
    m_drawCount = numVertices;

    // below tells OpenGL to create our vertexArray(s) and where to store them
    // takes 2 parameters, the number of vertexArrays you want to create and the location to store
    //  the object (our m_vertexArrayObject)
    glGenVertexArrays(1, &m_vertexArrayObject);

    // now that we have generated our vertexArrays we bind them so that any operation that would effect a
    //  vertex object will effect the specified object, so I would likely need to do this multiple times for 
    //  multiple vertex arrays. Next we do operations on the vertex arrays before stopping binding
    glBindVertexArray(m_vertexArrayObject);


    // any block of data on the GPU is called a "buffer", and that is how we handle our data
    
    // below allocates blocks of data, "buffers", on the GPU.
    // Parameters: the number of buffers to generate, a pointer to our place to store our buffers (does not need "&"" because is an array) 
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    // just like we bind our vertexArray(s) we need to bind our buffers
    // Parameters: we need to tell OpenGL how to interperate this buffer with a GLenum, then the array containing our buffer
    //      our enum below tells OpenGL to interpperate our vertexes as arrays
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    
    // now that we have an array to store our vertex data in we need to put our vertex data into it
    // below does exactly what it says, puts the data it is given into a given buffer, "moving it from RAM to the GPU sort of".
    // parameters: GLenum target, GLsizeiptr size (numVerticies * size in bytes of Vertex* verticies[0]), const void *data, GLenum usage
    //      the final enum tries to tell the GPU where to store the data we pass in, GL_STATIC_DRAW means it will put it in a place where it doesnt need wuick access
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
    
    // we now have the data on the GPU and need to tell enable 
    // when the gpu is trying to draw something it needs to run through it in sequential order,
    //  looking at all of the vertexes attributes grouped together by type, meaning all instances of vertex "glm::vec3 pos" one after the other,
    //  before moving on to look at another attribute. This is where vertex attribute arrays come in,
    //  they group attribute data of multiple vertex instances together into one array for efficency of reading

    // below tells OpenGL that we will have an attribute array 0
    glEnableVertexAttribArray(0);
    // we then have to tell OpenGL how to read it as an array
    // parameters: we have to tell it what attrib array we will use, how many pieces of data will we go through (3 here because glm::vec3 pos has 3 coordinates), 
    //      how the data is stored (here GL_FLOAT), boolean GL_normilization, how much data to skip before finiding the next piece of attrib data (here 0, 
    //          because we only have one AtrribArray so it does not need to skip data), how far in it needs to start from the beginning to reach the first piece of data (here 0 to start at beginning)
    // parameters: GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // we now have now generated and bound our vertexes, created and bound buffers, put the vertex data into our buffer,
    //      created vertex attribute arrays and told OpenGL how to read the vertex arrays
    // We now have all our data organized to draw and can finish binding our vertex arrays

    // to "stop binding vertex arrays" we do below, which says that any operation we do that would effect a
    //  vertex object will not effect objects after this point
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    // just as before we delete things in reveres order of creating them
    //  just like glGenVertexArrays() we enter the number of vertex arrays to delete and where to delete from
    glDeleteVertexArrays(1, &m_vertexArrayObject);

}

void Mesh::Draw() {
    // just like we opened m_vertexArrayObject in our constructor for operations, we again need to open it up here
    glBindVertexArray(m_vertexArrayObject);

    // below tells OpenGL to draw our vertex arrays and how to do it
    // paramters: a GLenum for what type of things we want to draw, where to start in our buffer to read what to draw,
    //      and finally where to finish drawing (how many verticies to draw in this case)
    // parameters: GLenum mode, GLint first, GLsizei count
    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    // this stops binding operations to m_vertexArrayObject
    glBindVertexArray(0);
}