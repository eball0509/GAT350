#include "Scene.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "Tracer.h"
#include "ETime.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;


void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples, int depth)
{
	Time frameTimer;
	Time scanLineTimer;

	for (int y = 0; y < framebuffer.m_height; y++)
	{
		scanLineTimer.Reset();
		for (int x = 0; x < framebuffer.m_width; x++)
		{
			color3_t color { 0 };

			for (int i = 0; i < numSamples; i++)
			{
				glm::vec2 pixel{ x, y };
				pixel += glm::vec2{ 0, 1 };
				glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };

				point.y = 1 - point.y;

				ray_t ray = camera.GetRay(point);


				color += Tracer::Trace(*this, ray, 0.001f, 100.0f, depth) ;
			}
			
			color = color / (float)numSamples;

			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
		std::cout << "y: " << y << " - Release Time " << scanLineTimer.GetElapsedTime() << endl;
	}
	std::cout << "frame time: " << frameTimer.GetElapsedTime() << endl;
}
