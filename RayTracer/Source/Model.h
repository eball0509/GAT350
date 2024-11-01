#pragma once
#include "Color.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "SceneObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
using namespace std;

using vertex_t = glm::vec3;
using verticies_t = vector<vertex_t>;

class Model : public SceneObject
{

public:

	Model(shared_ptr<Material> material) : SceneObject{ material } {}

	Model(const verticies_t& vertices, std::shared_ptr<Material> material) : SceneObject{ material }, m_verticies{ vertices } {}

	bool Load(const string& filename);

	// Inherited via SceneObject
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

private:

	verticies_t m_verticies;


	

};