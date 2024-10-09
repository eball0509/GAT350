#pragma once
#include "FrameBuffer.h"
#include <string>
#include <vector>
using namespace std;


class Image 
{
public:
	Image() = default;
	~Image() = default;

	bool Load(const string& filename);

	friend class Framebuffer;

public:
	int m_width{ 0 };
	int m_height{ 0 };

	vector<color_t> m_buffer;

};