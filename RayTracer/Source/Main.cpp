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
#include "Plane.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    Time time;
    Renderer* renderer = new Renderer();

    renderer->Initialize();
    renderer->CreateWindow("Ray Tracer", 600, 800);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(*renderer, renderer->GetWidth(), renderer->GetHeight());

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ 0,0,-20 }, { 0, 0, 0 });

    Scene scene;
    shared_ptr<Material> material = make_shared <Lambertian>(color3_t{ 1, 0, 0 });
    shared_ptr<Material> gray = make_shared<Lambertian>(color3_t{ 0.5f });
    shared_ptr<Material> red = make_shared<Metal>(color3_t{ 1, 0, 0 }, 1);
    shared_ptr<Material> blue = make_shared<Metal>(color3_t{ 0, 0, 1 }, 1);

    auto object = make_unique<Sphere>(glm::vec3{ 0, -5, -40 }, 2.0f, blue);
    auto plane = make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, gray);


    scene.AddObject(move(object));
    scene.AddObject(move(plane));

    vector<shared_ptr<Material>> materials;

    materials.push_back(red);
    materials.push_back(gray);
    materials.push_back(blue);


    for (int i = 0; i < 15; i++)
    {
        auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), random(2), materials[random(materials.size())]);
        scene.AddObject(std::move(object));
    }

    SetBlendMode(BlendMode::Normal);

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

        framebuffer.Clear(ColorConvert(color4_t{ 0, 0, 0, 1 }));

        scene.Render(framebuffer, camera);

        framebuffer.Update();

        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
};