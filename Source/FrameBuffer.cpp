#include "FrameBuffer.h"
#include "Renderer.h"

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);
	if (m_texture == nullptr) {
		cerr << "Error initializing SDL: " << SDL_GetError() << endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL , m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	fill(m_buffer.begin(), m_buffer.end(), color);
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	if (x >= m_width || x < 0 || y >= m_height) return;

	m_buffer[x + (y * m_width)] = color;
}

void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	if (x + w < 0 || x >= m_width || y + h < 0 || y >= m_height) return;

	int x1 = max(x, 0);
	int x2 = min(x + w, m_width);
	int y1 = max(y, 0);
	int y2 = min(y + h, m_height);

	for (int sy = y1; sy < y2; sy++) {

		int index = x1 + sy * m_width;
		fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1), color);
	}
}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	

	if (dx == 0) 
	{
		if (y1 > y2) swap(y1, y2);
		for (int y = y1; y < 2; y++) 
		{
			m_buffer[x1 + y * m_width] = color;
		}

	}
	else
	{
		float m = dy / (float)dx;
		float b = y1 - (m * x1);

		if (abs(dx) > abs(dy)) {

			for (int x = x1; x <= x2; x++)
			{
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}

		}
		else
		{
			for (int y = y1; y < y2; y++) {

				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;
			}
		}
	
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	bool steep = (abs(dx) > abs(dy));
	if (steep)
	{
		swap(x1,y1);
		swap(x2, y2);
	}

	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	dx = x2 - x1;
	dy = abs(y2 - y1);

	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;

	for (int x = x1, y = y1; x <= x2; x++)
	{
		(steep) ? DrawPoint(y, x, color) : DrawPoint(x, y, color);
		error -= dy;

		if (error < 0) 
		{
			y += ystep;
			error += dx;
		}
	}
	
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{

}
