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

    renderer->Initialize();
    renderer->CreateWindow("2D", 600, 800);

    Framebuffer framebuffer(*renderer, renderer->GetWidth(), renderer->GetHeight());
    Camera camera(renderer->GetWidth(), renderer->GetHeight());
    camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    camera.SetProjection(120.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ {0, 0, -20} };

    /*
    Image image;
    image.Load("image.png");
    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 128);
    SetBlendMode(BlendMode::Multiply);
    */
    

    shared_ptr <Model> model = make_shared<Model>();
    model->Load("sphere.obj");
    model->SetColor({ 255,0,0,255 });

    Transform sphereTransformation{ {0, 0, 0}, glm::vec3{0, 0, 90}, glm::vec3{3} };
    Actor actor(sphereTransformation, model);

    vector<unique_ptr<Actor>> actors;

    for (int i = 0; i < 20; i++)
    {
        Transform transform{ {randomf(-10.0f, 10.0f), randomf(-10.0f, 10.0f), randomf(-10.0f, 10.0f)}, glm::vec3{0}, glm::vec3{2} };
        unique_ptr<Actor> actor = make_unique<Actor>(transform, model);
        actors.push_back(move(actor));
    };

   

    SetBlendMode(BlendMode::Normal);
    


    /*
    verticies_t verticies = { {-5, 5, 0},
                              {5, 5, 0}, 
                              {-5, -5, 0} };
    Model model{verticies, {0, 255, 0, 255 } };

    Transform transform{ {240, 240, 0}, glm::vec3{0}, glm::vec3{4} };
    */


   

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

        
        //framebuffer.DrawImage(100, 100, image);
        //framebuffer.DrawImage(mx, my, imageAlpha);

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


        if (input.GetMouseButtonDown(2)) {
            input.SetRelativeMode(true);

            glm::vec3 direction{ 0 };
            if (input.GetKeyDown(SDL_SCANCODE_RIGHT))direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_LEFT))direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_UP))direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_DOWN))direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W))direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S))direction.z = -1;
                        
            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;
            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };
            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();

        }
        else {
            input.SetRelativeMode(false);
        }
      
        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

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