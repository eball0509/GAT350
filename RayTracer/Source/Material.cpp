#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter)
{

	scatter.origin = raycastHit.point;
	scatter.direction = raycastHit.normal + randomOnUnitSphere();
	attenuation = m_albedo;

	return true;
}

bool Metal::Scatter(const ray_t ray, const raycastHit_t& raycastHIt, color3_t& attenuation, ray_t& scatter)
{
	glm::vec3 reflected = Reflect(ray.direction, raycastHIt.normal);

	scatter = ray_t{ raycastHIt.point, reflected + (randomOnUnitSphere() * m_fuzz) };

	attenuation = m_albedo;

	return Dot(scatter.direction, raycastHIt.normal) > 0;
}
