#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"

color3_t Tracer::Trace(Scene& scene, const ray_t& ray)
{
	color3_t color{ 0 };

	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray))
		{
			return object->GetMaterial().lock()->GetColor();
		}
	}

	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	color = Lerp(color3_t{1, 0.35f, 1}, color3_t{0.5f, 0.3f, 1.0f}, t);

	return color;
}
