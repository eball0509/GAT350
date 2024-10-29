#include "Plane.h"
#include "MathUtils.h"
#include <glm/ext/quaternion_geometric.hpp>

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{

    float denominator = glm::dot(ray.direction, m_normal);
    if (approximately(denominator, 0)) return false;

    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0) return false;

    if (t <= minDistance || t >= maxDistance) return false;

    raycastHit.distance = t;
    raycastHit.normal = m_normal;
    raycastHit.point = ray.At(t);
    raycastHit.material = GetMaterial();

    return true;
}
