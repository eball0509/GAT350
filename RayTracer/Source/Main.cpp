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
#include "Material.h"
#include "Triangle.h"

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
    shared_ptr<Material> green = make_shared<Emissive>(color3_t{ 0, 1, 0 }, 2);
    shared_ptr<Material> purple = make_shared<Emissive>(color3_t{ 0.5f, 0, 0.5f }, 2);
    shared_ptr<Material> red = make_shared<Metal>(color3_t{ 1, 0, 0 }, 1);
    shared_ptr<Material> blue = make_shared<Emissive>(color3_t{ 0, 0, 1 }, 3);
    shared_ptr<Material> white = make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.33f);
    shared_ptr<Material> planeColor = make_shared<Lambertian>(color3_t{ 0, 0, 0 });

    

    auto object = make_unique<Sphere>(glm::vec3{ 0, -5, -40 }, 2.0f, blue);
    auto plane = make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, planeColor);
    auto model = make_unique<Model>(planeColor);
    model->Load("cube.obj");
    auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 2, 0 }, glm::vec3{ 0, 4, 0 }, glm::vec3{ 2, 2, 0 }, planeColor);
    
    

    scene.AddObject(move(triangle));
    scene.AddObject(move(object));
    scene.AddObject(move(model));

    vector<shared_ptr<Material>> materials;

    materials.push_back(white);
    materials.push_back(red);
    materials.push_back(blue);
    materials.push_back(green);
    materials.push_back(purple);



    /*for (int i = 0; i < 2; i++)
    {
        auto object = make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), random(4), materials[random(materials.size())]);
        scene.AddObject(move(object));
    }*/

   

    scene.AddObject(move(plane));

    SetBlendMode(BlendMode::Normal);

    scene.Render(framebuffer, camera, 1, 50);


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

       
        framebuffer.Update();

        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
};