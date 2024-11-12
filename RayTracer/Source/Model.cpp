#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>


void Model::Update()
{
	for (int i = 0; i < m_local_verticies.size(); i++)
	{
		m_verticies[i] = m_transform * glm::vec4{ m_local_verticies[i], 1 };
	}

	m_center = glm::vec3{ 0 };
	for (auto& vertex : m_verticies)
	{
		m_center += vertex;
	}
	m_center /= (float)m_verticies.size();

	m_radius = 0;
	for (auto& vertex : m_verticies)
	{
		float radius = glm::length(vertex - m_center);
		m_radius = glm::max(radius, m_radius);
	}
}

bool Model::Load(const std::string& filename)
{
	ifstream stream(filename);

	if (!stream.is_open())
	{
		cerr << "File did not open: " << filename << endl;
		return false;
	}

	verticies_t vertices;
	string line;
	while (getline(stream, line))
	{
		if (line.substr().find("v ") == 0)
		{
			istringstream sstream{ line.substr(2) };
			glm::vec3 position;

			sstream >> position.x;
			sstream >> position.y;
			sstream >> position.z;

			vertices.push_back(position);
		}

		else if (line.substr().find("f ") == 0)
		{
			
			istringstream sstream{ line.substr(2) };
			string str;
			while (getline(sstream, str, ' '))
			{
				istringstream sstream(str);
				string indexString;

			
				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 }; 
				while (getline(sstream, indexString, '/'))
				{
					if (!indexString.empty())
					{
						istringstream indexStream{ indexString };
						indexStream >> index[i];
					}
					i++;
				}

				if (index[0] != 0)
				{
					glm::vec3 position = vertices[index[0] - 1];
					m_local_verticies.push_back(position);
				}
			}
		}
	}
	m_verticies.resize(m_local_verticies.size());

	stream.close();

	return true;
}

bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)

{

	// check for bounding sphere raycast

	float t;
	if (!Sphere::RayCast(ray, m_center, m_radius, minDistance, maxDistance, t)) return false;


	// check cast ray with mesh triangles 

	for (size_t i = 0; i < m_verticies.size(); i += 3)
	{
		float t;

		if (Triangle::RayCast(ray, m_verticies[i], m_verticies[i + 1], m_verticies[i + 2], minDistance, maxDistance, t))

		{
			// set raycast hit
			raycastHit.distance = t;
			raycastHit.point = ray.At(t);

			// set edges of the triangle
			glm::vec3 edge1 = m_verticies[i + 1] - m_verticies[i];
			glm::vec3 edge2 = m_verticies[i + 2] - m_verticies[i];

			// calculate triangle normal (edge1 x edge2) [x = cross product]
			raycastHit.normal = glm::normalize(Cross(edge1, edge2));
			raycastHit.material = GetMaterial();

			return true;
		}
	}
	return false;
}
