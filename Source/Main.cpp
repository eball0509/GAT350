#include "Renderer.h"
#include "FrameBuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include <iostream>
#include "GLM.h"
using namespace std;

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer();

    Image image;
    image.Load("image.png");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 128);

    renderer->Initialize();
    renderer->CreateWindow("2D", 800, 600);

    Framebuffer framebuffer(*renderer, 800, 600);
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        // clear screen
        SDL_SetRenderDrawColor(renderer->m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer->m_renderer);


        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        for (int i = 0; i < 20; i++)
        {
            int x1 = rand() % framebuffer.m_width;
            int y1 = rand() % framebuffer.m_height;
            int x2 = rand() % framebuffer.m_width;
            int y2 = rand() % framebuffer.m_height;
            //framebuffer.DrawPoint(x1, y1, { 255,255,255,255 });
            //framebuffer.DrawRect(x1, y1, x2, y2, { 255,255,255,255 });
            //framebuffer.DrawLine(x1, y1, x2, y2, { 255, 255, 255, 255 });
            //framebuffer.DrawCircle(400, 200, 100, {255,255,255,255});
            //framebuffer.DrawTriangle(100,400,300,400,200,300, {255,255,255,255});
            //framebuffer.DrawLine(100, 300, 200, 500, { 255,255,255,255 });
            //framebuffer.DrawImage(x1, y1, image);

        }
        

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        framebuffer.DrawImage(100, 100, image);
        framebuffer.DrawImage(mx, my, imageAlpha);

        //framebuffer.DrawLinearCurve(100, 100, 200, 200, {255,255,255,255});
        //framebuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, { 255,255,255,255 });
        //framebuffer.DrawCubicCurve(100, 200, mx, my, 200, 100, 200, 200, { 255, 255, 255, 255 });
        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::Brightness(framebuffer.m_buffer, -50);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 200, 50, -50);
        //PostProcess::NoiseEffect(framebuffer.m_buffer, 40);
        //PostProcess::Threshold(framebuffer.m_buffer, 150);
        //PostProcess::Posterization(framebuffer.m_buffer, 6);

        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 6);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

        framebuffer.Update();

        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}