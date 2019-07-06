#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
// GLM does not include transformation functions when you include glm.hpp
// they must be included seperately below
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

// this class will be simple, it could only be a struct
// we will acually use our vertex shader to make changes to our position
class Transform {
public:
    // we will have 3 ways of moving our object: position, orientation and scale
    // our constructor will take in a reference to each of these types of transformations
    // we set each paramenter below to default to an empty vec3, scale starts with 1.0f for each coord
    Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
        m_pos(pos), m_rot(rot), m_scale(scale) {};

    // below is a function to get matrixes to represent transformations
    // matrixes are custimarily called Models in OpenGL
    glm::mat4 GetModel() const {
        // we can use the included transform.hpp functions below to create a matrix for transformations
        glm::mat4 posMatrix = glm::translate(m_pos);
        glm::mat4 scaleMatrix = glm::scale(m_scale);
        // rotation is different, roation has challenges that require special 
        // glm does not have a customary method to do this, we have to make our own
        // glm::rotate() takes an angle and a axis of rotation glm::vec3(x, y, z)
        glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1,0,0));
        glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0,1,0));
        glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0,0,1));
        // we now need to combine our rotations with multiplication
        // the matrixes must be multiplied in opposite orer of which you want them applied
        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        // we now have 5 matrixes representing our possible transformations

        // again we need to combine our matrixes with multiplication in opposite order of how we want them applied
        // the orderin which we apply these transformations matters, example changing the position then trying to rotate could cause "orbiting"
        
        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline glm::vec3& GetPos() {return m_pos;};
    inline glm::vec3& GetRot() {return m_rot;};
    inline glm::vec3& GetScale() {return m_scale;};

    inline void SetPos(const glm::vec3& pos) { m_pos = pos;};
    inline void SetRot(const glm::vec3& rot) { m_pos = rot;};
    inline void SetScale(const glm::vec3& scale) { m_pos = scale;};

private:
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;
};

#endif