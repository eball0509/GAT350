#pragma once
#include "SceneObject.h"
#include "glm/glm.hpp"

class Plane : public SceneObject
{

public:

	Plane() = default;
	Plane(const Transform& transform, shared_ptr<Material> material) : SceneObject{transform, material} {}
	

	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

	static bool RayCast(const ray_t& ray,const glm::vec3& point, const glm::vec3& normal, float minDistance, float maxDistance, float& t);

};