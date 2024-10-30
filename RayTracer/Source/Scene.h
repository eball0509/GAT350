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

	void Render(class Framebuffer& framerbuffer, const class Camera& camera, int numSpamples = 10, int depth = 5);
	void AddObject(unique_ptr<class SceneObject> object) { m_objects.push_back(move(object)); }

	friend class Tracer;

private:

	vector<unique_ptr<class SceneObject>> m_objects;

};