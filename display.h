#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display {
public:
    Display(int w, int h, const std::string title);
    virtual ~Display();
    bool IsClosed() {return m_isClosed;};
    void Clear(float r, float g, float b, float a);
    void Update();

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif