#pragma once
#include "Sphere.h"
#include "Tracer.h"
#include <vector>
#include <memory>
using namespace std;

class Scene 
{

public:
	Scene() = default;

	void Update();
	void Render(class Framebuffer& framerbuffer, const class Camera& camera, int numSpamples = 10, int depth = 5);
	void AddObject(unique_ptr<class SceneObject> object) { m_objects.push_back(move(object)); }

	void setSky(const color3_t& skyBottom, const color3_t& skyTop)
	{
		m_skyBottom = skyBottom;
		m_skyTop = skyTop;
	}

	friend class Tracer;

private:

	vector<unique_ptr<class SceneObject>> m_objects;
	color3_t m_skyBottom{ 1 };
	color3_t m_skyTop{ 0.5, 0.7, 1 };

};