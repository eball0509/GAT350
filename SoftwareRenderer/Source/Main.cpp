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

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    Time time;
    Input input;
    input.Initialize();

    Renderer* renderer = new Renderer();

    // Window Creation
    renderer->Initialize();
    renderer->CreateWindow("2D", 600, 800);

    Framebuffer framebuffer(*renderer, renderer->GetWidth(), renderer->GetHeight());

    //Loading the Background Image
    Image image;
    image.Load("background.png");


    // Creating the camera
    Camera camera(renderer->GetWidth(), renderer->GetHeight());
    camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    camera.SetProjection(120.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ {0, 0, -20} };


    // Creating the models: 1
    shared_ptr <Model> model = make_shared<Model>();
    model->Load("sphere.obj");
    model->SetColor({ 165,0,128,255 });
    Transform modelTranfsorm{ {0, 0, 0}, glm::vec3{0, 0, 90}, glm::vec3{3} };
    Actor actor(modelTranfsorm, model);

    // 2
    shared_ptr <Model> model2 = make_shared<Model>();
    model2->Load("cube.obj");
    model2->SetColor({ 0,0,255,255 });
    Transform model2Tranfsorm{ {0, 0, 0}, glm::vec3{0, 0, 90}, glm::vec3{3} };
    Actor actor2(model2Tranfsorm, model2);

    // 3
    shared_ptr <Model> model3 = make_shared<Model>();
    model3->Load("torus.obj");
    model3->SetColor({ 255,255,255,255 });
    Transform model3Tranfsorm{ {0, 0, 0}, glm::vec3{0, 0, 90}, glm::vec3{3} };
    Actor actor3(model3Tranfsorm, model3);

    // Actor vector creation to load all actors
    vector<unique_ptr<Actor>> actors;


    // pushes all actors into the vector above, allowing all to be written later
    for (int i = 0; i < 8; i++)
    {
        // transforms for every actor: 1
        Transform transform{ {randomf(-20.0f, 20.0f), randomf(-20.0f, 20.0f), randomf(-20.0f, 20.0f)}, glm::vec3{randomf(1.0f, 180.0f)}, glm::vec3{randomf(2.0f, 7.0f)}};
        // 2
        Transform transform2{ {randomf(-40.0f, 40.0f), randomf(-40.0f, 40.0f), randomf(-40.0f, 40.0f)}, glm::vec3{randomf(1.0f, 180.0f)}, glm::vec3{randomf(2.0f, 6.0f)} };
        // 3
        Transform transform3{ {randomf(-40.0f, 40.0f), randomf(-40.0f, 40.0f), randomf(-40.0f, 40.0f)}, glm::vec3{randomf(1.0f, 180.0f)}, glm::vec3{randomf(2.0f, 5.0f)} };
        
        // Making the models actors: 1
        unique_ptr<Actor> actor = make_unique<Actor>(transform, model);
        // 2
        unique_ptr<Actor> actor2 = make_unique<Actor>(transform2, model2);
        // 3
        unique_ptr<Actor> actor3 = make_unique<Actor>(transform3, model3);
        
        // Pushing the actors onto the vector
        actors.push_back(move(actor));
        actors.push_back(move(actor2));
        actors.push_back(move(actor3));
    };
    
    SetBlendMode(BlendMode::Normal);

    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();

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
        
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        framebuffer.DrawImage(1,1, image);
        
        if (input.GetMouseButtonDown(2)) {
            input.SetRelativeMode(true);

            glm::vec3 direction{ 0 };
            if (input.GetKeyDown(SDL_SCANCODE_D))direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_A))direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W))direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S))direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_Q))direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_E))direction.z = -1;
                        
            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;
            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };
            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();

        }
        else {
            input.SetRelativeMode(false);
        }
      
        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        // Draws every actor 
        for (auto& actor : actors) {
            actor->Draw(framebuffer, camera);
        }

        framebuffer.Update();
        *renderer = framebuffer;

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}