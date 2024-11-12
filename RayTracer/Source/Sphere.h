#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include <glm/glm.hpp>
using namespace std;

class Sphere : public SceneObject
{

public:
	Sphere() = default;
	Sphere(const Transform& transform, float radius, shared_ptr<Material> material) : SceneObject{ transform, material }, m_radius{radius} {}
	Sphere(const glm::vec3& center, float radius, shared_ptr<Material> material) : SceneObject{ material }, m_center{ center }, m_radius{ radius } {}

	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

	static bool RayCast(const ray_t& ray, const glm::vec3& center, float radius, float minDistance, float maxDistance, float& t);

private:
	glm::vec3 m_center{ 0 };
	float m_radius{ 0 };

};