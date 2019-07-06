#version 120

// 
attribute vec3 position;

// OpenGL has a variable type called uniform that allows us to use transformations
uniform mat4 transform;
// then once we have that matrix, we can apply it to each vertex in the main() function

void main(){
    
    // code was "gl_Position = vec4(position, 1.0);" but by multiplying by the new transform variable to make our transformations
    gl_Position = transform * vec4(position, 1.0);
    // we then need some how get our data from the Transform class GetModel()
    // the second parameter is the scale to which the transformation will effect the position change
    // our shader class also needs to to take in this new functionality
}