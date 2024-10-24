#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>


void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera)
{
	
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
