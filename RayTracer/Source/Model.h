#pragma once
#include "Color.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
using namespace std;

using vertex_t = glm::vec3;
using verticies_t = vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const verticies_t& verticies, const color_t& color) : m_verticies{ verticies }, m_color{ color } {}

	void Draw(Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera);
	bool Load(const string& filename);
	void SetColor(color_t color) { m_color = color; }
public:
	verticies_t m_verticies;
	color_t m_color{0};
};