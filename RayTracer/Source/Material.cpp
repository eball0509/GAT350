#include "Material.h"
#include "Random.h"


bool Lambertian::Scatter(const ray_t ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter)
{
	scatter.origin = raycastHit.point;
	scatter.direction = raycastHit.normal + randomOnUnitSphere();
	attenuation = m_albedo;

	return true;
}

bool Metal::Scatter(const ray_t ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter)
{
	glm::vec3 reflected = Reflect(ray.direction, raycastHit.normal);

	scatter = ray_t{ raycastHit.point, reflected + (randomOnUnitSphere() * m_fuzz) };

	attenuation = m_albedo;

	return Dot(scatter.direction, raycastHit.normal) > 0;
}

bool Dielectric::Scatter(const ray_t ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter)
{
	glm::vec3 outNormal;
	float ni_over_nt;
	float cosine;

	// check if we are hitting from the outside
	if (glm::dot(ray.direction, raycastHit.normal) < 0)
	{
		outNormal = raycastHit.normal;
		ni_over_nt = 1.0f / m_ri;
		cosine = glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
	}
	else
	{
		outNormal = -raycastHit.normal;
		ni_over_nt = m_ri;
		cosine = m_ri * glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
	}

	glm::vec3 refracted;
	float reflectProb = 1.0f;

	if(Refract(ray.direction, raycastHit.normal, m_ri, refracted))
	{
		reflectProb = Schlick(cosine, m_ri);
	}

	glm::vec3 reflected = Reflect(ray.direction, raycastHit.normal);

	scatter = (randomf() < reflectProb ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted });

	scatter.origin = raycastHit.point;
	scatter.direction = refracted;

	attenuation = m_albedo;

	return true;
}
