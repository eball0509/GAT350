#pragma once
#include "SceneObject.h"
#include <glm/glm.hpp>
using namespace std;

class Sphere : public SceneObject
{

public:
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, shared_ptr<Material> material) : SceneObject{ material }, m_center{ center }, m_radius{ radius } {}

private:
	glm::vec3 m_center{0};
	float m_radius{0};


	// Inherited via SceneObject
	bool Hit(const ray_t& ray) override;

};