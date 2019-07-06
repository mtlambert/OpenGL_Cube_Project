#include "shader.h"

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);



Shader::Shader (const std::string fileName) {
    m_program = glCreateProgram();

    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
  
    for (unsigned int i=0; i<NUM_SHADERS; i++){
        glAttachShader(m_program, m_shaders[i]);
    }

    glBindAttribLocation(m_program, 0, "position");

    glLinkProgram(m_program);

    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

    // we then need to tell OpenGL which unifroms to us
    // the parameters are our shader program and then tell it what to look for in our shader file
    m_uniforms[TRANSFORM_U_] = glGetUniformLocation(m_program, "transform");
}

void Shader::Bind() {
    glUseProgram(m_program);
}

Shader::~Shader () {
    for (unsigned int i=0; i < NUM_SHADERS; i++){
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    
    glDeleteProgram(m_program);

}

static std::string LoadShader (const std::string& fileName) {
    std::ifstream file;
    file.open(fileName.c_str());
    std::string output;
    std::string line;
    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    return output;
}

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

static GLuint CreateShader(const std::string& text, GLenum shaderType) {    
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)
        std::cerr << "Shader creation failed" << std::endl;
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringsLength[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringsLength[0] = text.length();
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
    glCompileShader(shader);
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");
    return shader;
}


void Shader::Update(const Transform& transform) {
    glm::mat4 model = transform.GetModel();    

    // openGL has a function to update uniforms, used below
    // openGL has a long list of functions to update different types of uniforms
    // in this case we are looking to update a Matrix4
    // parameters: GLint location, GLsizei count, GLboolean transpose, const GLfloat *value(our data)
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U_], 1, GL_FALSE, &model[0][0]);
}