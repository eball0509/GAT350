#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

bool Image::Load(const string& filename)
{
	int channels;
	uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 4);
	if (!data) 
	{
		cerr << "Error loading image: " << filename << endl;
		return false;
	}

	m_buffer.resize(m_width * m_height);

	memcpy(m_buffer.data(), data, m_width * m_height * sizeof(color_t));

	stbi_image_free(data);

	return true;
}
