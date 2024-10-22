#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>


void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera)
{
	for (int i = 0; i < m_verticies.size(); i+=3)
	{
		vertex_t p1 = model * glm::vec4{ m_verticies[i + 0], 1 };
		vertex_t p2 = model * glm::vec4{ m_verticies[i + 1], 1 };
		vertex_t p3 = model * glm::vec4{ m_verticies[i + 2], 1 };

		p1 = camera.ModelToView(p1);
		p2 = camera.ModelToView(p2);
		p3 = camera.ModelToView(p3);

		glm::ivec2 s1 = camera.ViewToScreen(p1);
		glm::ivec2 s2 = camera.ViewToScreen(p2);
		glm::ivec2 s3 = camera.ViewToScreen(p3);

		if (s1.x == -1 || s1.y == -1 || s2.x == -1 || s2.y == -1 || s3.x == -1 || s3.y == -1)
		{
			continue;
		}

		framebuffer.DrawTriangle((int)s1.x, (int)s1.y, (int)s2.x, (int)s2.y, (int)s3.x, (int)s3.y, m_color);
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
					m_verticies.push_back(position);
				}
			}
		}
	}
	stream.close();

	return true;
}
