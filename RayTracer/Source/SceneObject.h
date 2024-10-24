#pragma once
#include "Material.h"
#include "Ray.h"
#include <memory>
using namespace std;

class SceneObject
{

public:
	SceneObject() = default;
	SceneObject(shared_ptr<Material> material) : m_material{ material } {}

	virtual bool Hit(const ray_t& ray) = 0;

	weak_ptr<class Material> GetMaterial() { return m_material; }

protected:
	shared_ptr<class Material> m_material;
};