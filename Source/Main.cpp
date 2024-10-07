#include "Renderer.h"
#include "FrameBuffer.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer();

    renderer->Initialize();
    renderer->CreateWindow("2D", 800, 600);

    Framebuffer framebuffer(*renderer, 800, 600);

    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer->m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer->m_renderer);


        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        for (int i = 0; i < 100; i++)
        {
            int x1 = rand() % framebuffer.m_width;
            int y1 = rand() % framebuffer.m_height;
            int x2 = rand() % framebuffer.m_width;
            int y2 = rand() % framebuffer.m_height;
            //framebuffer.DrawPoint(x1, y1, { 255,255,255,255 });
            //framebuffer.DrawRect(x1, y1, x2, y2, { 255,255,255,255 });
            //framebuffer.DrawLine(x1, y1, x2, y2, { 255, 255, 255, 255 });
            framebuffer.DrawCircle(400, 200, 10, {255,255,255,255});
            framebuffer.DrawTriangle(100,400,300,400,200,300, {255,255,255,255});
            framebuffer.DrawLine(100, 300, 200, 500, { 255,255,255,255 });
        }

        framebuffer.Update();

        *renderer = framebuffer;


        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}