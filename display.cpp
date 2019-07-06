#include "display.h"

Display::Display(int w, int h, const std::string title) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();
    if (status != GLEW_OK) {
        std::cerr << "Unable to init GLEW" << std::endl;
    }
    m_isClosed = false;
}

Display::~Display() {
    
}

void Display::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update() {
    SDL_GL_SwapWindow(m_window);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_isClosed = true;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {


                    // move up
                    case SDLK_w:
                        m_transform->GetPos().y += 0.01;
                        continue;
                    // move down
                    case SDLK_s:
                        m_transform->GetPos().y -= 0.01;
                        continue;
                    // move left
                    case SDLK_a:
                        m_transform->GetPos().x -= 0.01;
                        continue;
                    // move right
                    case SDLK_d:
                        m_transform->GetPos().x += 0.01;
                        continue;



                    // zoom in
                    case SDLK_i:
                        m_transform->GetPos().z -= 0.01;
                        m_transform->GetScale().x *= 1.01;
                        m_transform->GetScale().y *= 1.01;
                        m_transform->GetScale().z *= 1.01;
                        continue;
                    // zoom out
                    case SDLK_o:
                        m_transform->GetPos().z += 0.01;
                        m_transform->GetScale().x *= 0.99;
                        m_transform->GetScale().y *= 0.99;
                        m_transform->GetScale().z *= 0.99;
                        continue;



                    // rotate top (flatten)
                    case SDLK_u:
                        m_transform->GetRot().x -= 0.01;
                        continue;
                    // rotate bottom
                    case SDLK_j:
                        m_transform->GetRot().x += 0.01;
                        continue;



                    // spin left
                    case SDLK_h:
                        m_transform->GetRot().z += 0.01;
                        continue;
                    // spin right
                    case SDLK_k:
                        m_transform->GetRot().z -= 0.01;
                        continue;
                    
                    

                    // flip left
                    case SDLK_q:
                        m_transform->GetRot().y -= 0.01;
                        continue;
                    // flip right
                    case SDLK_e:
                        m_transform->GetRot().y += 0.01;
                        continue;
                }
        }
    }
}

void Display::GetTransform(Transform* transform) {
    m_transform = transform;
}