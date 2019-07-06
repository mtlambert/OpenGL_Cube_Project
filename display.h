#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "mesh.h"
#include "transform.h"

class Display {
public:
    Display(int w, int h, const std::string title);
    virtual ~Display();
    bool IsClosed() {return m_isClosed;};
    void Clear(float r, float g, float b, float a);
    void Update();
    void SetTransform(Transform* transform);

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
    Transform* m_transform;
};

#endif