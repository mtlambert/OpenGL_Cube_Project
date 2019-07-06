#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>


class Vertex {
public:
    Vertex(const glm::vec3 pos) {
        this->pos = pos;
    }
    float GetPosX() const {return pos[0];};
    float GetPosY() const {return pos[1];};
    float GetPosZ() const {return pos[2];};

private:
    glm::vec3 pos;
};


class Mesh {
public: 
    Mesh(Vertex* vertices, unsigned int numVertices);
    virtual ~Mesh();

    void Draw();

    Vertex* GetVert() const {return m_vertices;};

    unsigned int GetDrawCount() {return  m_drawCount;};

private:
    enum {
        POSITION_VB, NUM_BUFFERS
    };
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount; 
    Vertex* m_vertices;
};


#endif