#include "Renderer.h"


void Renderer::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }
}

void Renderer::CreateWindow(string name, int width, int height)
{
        m_window = SDL_CreateWindow("2D",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    

}

void Renderer::CopyFrameBuffer(const Framebuffer framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}

void Renderer::operator=(const Framebuffer& framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}
