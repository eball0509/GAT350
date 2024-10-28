#include "Plane.h"
#include "MathUtils.h"
#include <glm/ext/quaternion_geometric.hpp>

bool Plane::Hit(const ray_t& ray)
{

    float denominator = glm::dot(ray.direction, m_normal);
    if (approximately(denominator, 0)) return false;

    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0) return false;

    return true;
}
