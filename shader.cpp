#include "shader.h"

// declaration for helper methods below, not included in shader.h
// loads the shader from a file and returns it line for line as a string
static std::string LoadShader(const std::string& fileName);
// checks out shader program we loaded for errors
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
// this will build our shader program, takes in the imported text data from above program
// and takes an GLenum of shader type, in this case a GL_VERTEX_SHADER and GL_FRAGMENT_SHADER
static GLuint CreateShader(const std::string& text, GLenum shaderType);



Shader::Shader (const std::string fileName) {
    // below is the object for our shader program, in order to use it we have to tell
    // openGL that this is our shader program so we call glCreateProgram(), and creates space on GPU for it
    // openGL then will return a number used to refernece the program which we stor in the below memeber
    m_program = glCreateProgram();

    // typically we would create an enum for our shader types, allowing us to more easily access them,
    // for simplicty sake we dont do that here and refere to them by index instead
    // this shader BELOW is our VERTEX SHADER then the FRAGMENT SHADER
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
    // in order to differentiate between the two shaders which will need to be loaded from 2 seperate files
    // we have added the file extensions ".vs" and ".fs" to our file names, but they are not standard file types

    // now that out shaders are built we have to add them to our GL Program, we do this by cyclind through our
    // m_shaders object for NUM_SHADERS times and use glAttachShader() to add each of our, 2 in this case, shaders
    // to our program
    for (unsigned int i=0; i<NUM_SHADERS; i++){
        glAttachShader(m_program, m_shaders[i]);
    }

    // this is very important below, forgetting it can cause hard to detect bugs down the road
    // make sure to do this before linking and validating the program
    // this gives OpenGL essentially a context for understanding our shader file? More detail to come
    // parameters: GLuint program, the attribute to be bound(which here is attrib 0), the variable to bind the attribute to
    glBindAttribLocation(m_program, 0, "position");

    // we next need to link our shaders to our program for compilation and then validate that we
    // ended with an actual valid shader
    // below allows us to link our added shaders to our program
    glLinkProgram(m_program);
    // now that we are added and linked we need to validate our shaders and check for errors, so we can use the
    // helper method below that we wrote to check if our finished shaders linked
    // below we pass out GLuint m_program representing our program, then what we are checking hich is GL_LINK_STATUS,
    //  a bool for whether or not this is a GLuint program, and finally the error message to return
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    // we can then check to see if the program is valid using a similar process
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

// this function tells OpenGL that we are going to use our shader program
void Shader::Bind() {
    // this sets the program we are going to use as a shader
    glUseProgram(m_program);
}

Shader::~Shader () {
    // just like in our Display class we must breakdown out objects after the program completes
    // we should break them down in reverse order of being build
    
    // here we loop through all of our shaders first detaching the link we made, then
    // deleting them
    for (unsigned int i=0; i < NUM_SHADERS; i++){
        // parameters: the GLuint program we are detaching from, the shader we are detaching
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    
    // this will delete our GLuint program free up the formally needed space on GPU
    glDeleteProgram(m_program);

}

static std::string LoadShader (const std::string& fileName) {
    // getting file
    std::ifstream file;
    file.open(fileName.c_str());
    // preping variables
    std::string output;
    std::string line;
    // check to see if file is open
    if (file.is_open()) {
        // file.good returns false if if any of the stream's error state flags (eofbit, failbit and badbit) is set.
        // essentially returns true while no errors sent from stream
        while (file.good()) {
            getline(file, line);
            // copying our file line for line into our output file to be returned for next function
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    // returns the file we copied line for line into output
    return output;
}

// used to check for shader errors. a GLuint is a basic program in OpenGL, so m_program in this case, then the error we are
//  checking for
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

// in this program we take in the shader program, then build it, compile it, and return it
static GLuint CreateShader(const std::string& text, GLenum shaderType) {
    
    // below does the inital creation of our shader
    GLuint shader = glCreateShader(shaderType);

    // checking to see if we were actually able to create a shader
    if (shader == 0)
        std::cerr << "Shader creation failed" << std::endl;

    // OpenGL is a C library so will require us to convert our string text into a c type string
    // we create a GLchar pointer to an array then store our text as a c_str() into it
    const GLchar* shaderSourceStrings[1];
    // I think we have GLint and GLchar and GLenum, because they are data types going to the GPU, where as
    // an int or a char or an enum would be on the CPU?
    // since we are converting our string to a C type string and C will want to know its size we create the below variable
    GLint shaderSourceStringsLength[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLength[0] = text.length();

    // we are now ready to have OpenGL compile our shader
    // below sends the source code to OpenGL to compiles our shaders
    // parameters: what we are compiling (the GLuint shader we made above), number of things to compile, source text for compilation, text length since this is in C
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
    // below actually does the compilation after recieving source code
    glCompileShader(shader);

    // now that it is compiled we need to check the shader for errors
    // parameters: what GLuint we are checking, what e are checking it for, is it a program(no just a shader), our error message
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");

    return shader;
}