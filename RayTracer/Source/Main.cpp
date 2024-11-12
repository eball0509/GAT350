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

void FinalScene(Scene& scene, Camera& camera);
void InitScene(Scene& scene);
void CornellBox(Scene& scene, Camera& camera);

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
    camera.SetView({ 0, 0, -12 }, { 0, 0, 0 });

    Scene scene;
    FinalScene(scene, camera);
    //InitScene(scene);
    //CornellBox(scene, camera);

    scene.Update();
    scene.Render(framebuffer, camera, 100, 6);
    framebuffer.Update();
  
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

        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
};

void FinalScene(Scene& scene, Camera& camera)
{
    camera.SetFOV(30.0f);

    // All Created Materials
    shared_ptr<Material> gunMetal = make_shared<Metal>(color3_t{ .5f, .52f, .53f }, 1);
    shared_ptr<Material> paynesGray = make_shared<Lambertian>(color3_t{ .21f, .19f, .29f });
    shared_ptr<Material> silver = make_shared<Dielectric>(color3_t{ .75f, .75f, .75f }, 1.33f);
    shared_ptr<Material> white = make_shared<Lambertian>(color3_t{ 1, 1, 1 });

    // (these arent added into the vector)
    shared_ptr<Material> sun = make_shared<Emissive>(color3_t{ 1, 1, 0 }, 6);
    shared_ptr<Material> planeCoral = make_shared<Lambertian>(color3_t{ 1, .49f, .31f });

    // All materials (except plane, and the light) moving onto the created vector
    vector<shared_ptr<Material>> materials;

    materials.push_back(gunMetal);
    materials.push_back(paynesGray);
    materials.push_back(silver);
    materials.push_back(white);

    // Adding random objects / shapes
    for (int i = 0; i < 3; i++)
    {
        auto object = make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 2.0f), gunMetal);
        scene.AddObject(std::move(object));

        auto object2 = make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 2.0f), paynesGray);
        scene.AddObject(std::move(object2));

        auto object3 = make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 2.0f), silver);
        scene.AddObject(std::move(object3));

        auto object4 = make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 2.0f), white);
        scene.AddObject(std::move(object4));
    }

    // Adding hand placed objects

    auto light = make_unique<Model>(Transform{ glm::vec3{0, 7, 0}}, sun);
    light->Load("models/torus.obj");
    scene.AddObject(move(light));

    auto model = make_unique<Model>(Transform{ glm::vec3{0, -2, -4}, glm::vec3{45, 0, 45}, glm::vec3{2, 2, 2} }, white);
    model->Load("models/cube.obj");
    scene.AddObject(move(model));

    auto sphere = make_unique<Sphere>(Transform{ glm::vec3{0, 1, 0}}, 1.0f, gunMetal);
    scene.AddObject(move(sphere));

    auto floor = make_unique<Plane>(Transform{ glm::vec3{0, -8, 0}, glm::vec3{0, 0, 0} }, planeCoral);
    scene.AddObject(move(floor));
}

void CornellBox(Scene& scene, Camera& camera)
{
    camera.SetFOV(60.0f);
    camera.SetView({ 0, 0, -10 }, { 0, 0, 0 });
    scene.setSky(color3_t{ 1 }, color3_t{ 1 });

    shared_ptr<Material> rightW = make_shared<Lambertian>(color3_t{ 0, 1, 0 });
    shared_ptr<Material> leftW = make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    shared_ptr<Material> other = make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    shared_ptr<Material> gray = make_shared<Lambertian>(color3_t{ .5f, .5f, .5f });
    shared_ptr<Material> blue = make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    shared_ptr<Material> light = make_shared<Emissive>(color3_t{ 1, 1, 1 }, 8);

    auto right = make_unique<Plane>(Transform{ glm::vec3{5, 0, 0}, glm::vec3{0, 0, -90} }, rightW);
    scene.AddObject(move(right));

    auto left = make_unique<Plane>(Transform{ glm::vec3{-5, 0, 0}, glm::vec3{0, 0, -270} }, leftW);
    scene.AddObject(move(left));

    auto otherFloor = make_unique<Plane>(Transform{ glm::vec3{0, -5, 0}, glm::vec3{0, 0, 0} }, other);
    scene.AddObject(move(otherFloor));

    auto otherBackWall = make_unique<Plane>(Transform{ glm::vec3{0, 0, 5}, glm::vec3{90, 0, 0} }, other);
    scene.AddObject(move(otherBackWall));

    auto otherFrontWall = make_unique<Plane>(Transform{ glm::vec3{0, 0, -12}, glm::vec3{-90, 0, 0} }, other);
    scene.AddObject(move(otherFrontWall));

    auto otherCeiling = make_unique<Plane>(Transform{ glm::vec3{0, 5, 0}, glm::vec3{0, 0, 0} }, other);
    scene.AddObject(move(otherCeiling));

    auto lightS = make_unique<Model>(Transform{ glm::vec3{0, 4.5f, 1,}, glm::vec3{90, 180, 0}, glm::vec3{1, 1, 2,}}, light);
    lightS->Load("models/quad.obj");
    scene.AddObject(move(lightS));

    auto model = make_unique<Model>(Transform{ glm::vec3{-1.5f, -4.4f, .6f}, glm::vec3{0, 0, 0} , glm::vec3{3, 2, 3} }, gray);
    model->Load("models/cube.obj");
    scene.AddObject(move(model));

    auto model2 = make_unique<Model>(Transform{ glm::vec3{2, -1.7f, 2}, glm::vec3{0, 0, 0} , glm::vec3{2, 7, 2} }, blue);
    model2->Load("models/cube.obj");
    scene.AddObject(move(model2));

}

void InitScene(Scene& scene)
{
    scene.setSky(HSVtoRGB(240.0f, 1, 0), HSVtoRGB(240.0f, 1, 1));

    shared_ptr<Material> green = make_shared<Emissive>(color3_t{ 0, 1, 0 }, 2);
    shared_ptr<Material> purple = make_shared<Emissive>(color3_t{ 0.5f, 0, 0.5f }, 2);
    shared_ptr<Material> red = make_shared<Metal>(color3_t{ 1, 0, 0 }, 1);
    shared_ptr<Material> blue = make_shared<Emissive>(color3_t{ 0, 0, 1 }, 3);
    shared_ptr<Material> white = make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.33f);
    shared_ptr<Material> black = make_shared<Lambertian>(color3_t{ 0, 0, 0 });
    shared_ptr<Material> planeColor = make_shared<Lambertian>(color3_t{ 1, 1, 1 });

    vector<shared_ptr<Material>> materials;

    materials.push_back(white);
    materials.push_back(red);
    materials.push_back(blue);
    materials.push_back(green);
    materials.push_back(purple);
    materials.push_back(black);

    for (int i = 0; i < 2; i++)
    {
        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 3.0f), materials[random(materials.size())]);
        scene.AddObject(std::move(object));
    }

    /*auto object = make_unique<Sphere>(glm::vec3{ 0, -5, -40 }, 2.0f, blue);
    scene.AddObject(move(object));*/

    auto triangle = std::make_unique<Triangle>(glm::vec3{ -2, 2, 0 }, glm::vec3{ 0, 4, 0 }, glm::vec3{ 2, 2, 0 }, black);
    scene.AddObject(move(triangle));

    auto model = make_unique<Model>(Transform{}, planeColor);
    model->Load("models/cube.obj");
    scene.AddObject(move(model));

    /*auto plane = make_unique<Plane>(Transform{ glm::vec3{0, -2, 0}, glm::vec3{0, 0, 20} }, planeColor);
     scene.AddObject(move(plane));*/
}