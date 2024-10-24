#include "Renderer.h"
#include "FrameBuffer.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Camera.h"
#include "Input.h"
#include "Color.h"
#include "Actor.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    Time time;
    Renderer* renderer = new Renderer();

    renderer->Initialize();
    renderer->CreateWindow("Ray Tracer", 600, 800);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(*renderer, renderer->GetWidth(), renderer->GetHeight());

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height};
    camera.SetView({ 0,0,-20 }, { 0, 0, 0 });
   
    Scene scene;

    shared_ptr<Material> material = make_shared <Material> (color3_t{ 1, 0, 0 });
    auto object = make_unique<Sphere>(glm::vec3{ 0, 0, -40 }, 2.0f, material);

    scene.AddObject(move(object));


    
    bool quit = false;
    while (!quit)
    {
        time.Tick();

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

        framebuffer.Clear(ColorConvert(color4_t{0, 0, 0, 1}));

        scene.Render(framebuffer, camera);

        framebuffer.Update();
       
        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}