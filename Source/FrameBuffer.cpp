#include "FrameBuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"

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
	color_t& dest = m_buffer[x + (y * m_width)];
	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawPointClip(int x, int y, const color_t& color)
{
	if (x >= m_width || x < 0 || y >= m_height) return;

	color_t& dest = m_buffer[x + (y * m_width)];
	dest = ColorBlend(color, dest);
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

	bool steep = (abs(dy) > abs(dx));
	if (steep)
	{
		swap(x1,y1);
		swap(x2,y2);
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
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::CreateCircle(int xc, int yc, int x, int y, const color_t& color)
{
	m_buffer[(xc + x) + ((yc + y) * m_width)] = color;
	m_buffer[(xc - x) + ((yc + y) * m_width)] = color;
	m_buffer[(xc + x) + ((yc - y) * m_width)] = color;
	m_buffer[(xc - x) + ((yc - y) * m_width)] = color;
	m_buffer[(xc + y) + ((yc + x) * m_width)] = color;
	m_buffer[(xc - y) + ((yc + x) * m_width)] = color;
	m_buffer[(xc + y) + ((yc - x) * m_width)] = color;
	m_buffer[(xc - y) + ((yc - x) * m_width)] = color;
}

void Framebuffer::DrawCircle(int xc, int yc, int rad, const color_t& color)
{
	int x = 0;
	int y = rad;
	int d = 3 - (2 * rad);

	CreateCircle(xc, yc, x, y, color);

	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d += 4 * (x - y) + 10;
		}
		else
		{
			d += (4 * x) + 6;
		}
		x++;

		CreateCircle(xc, yc, x, y, color);
	}
}

void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{
	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{

	int sx1 = Lerp(x1, x2, t1);
	int sy1 = Lerp(y1, y2, t1);

	float t2 = t1 + dt;

	int sx2 = Lerp(x1, x2, t2);
	int sy2 = Lerp(y1, y2, t2);

	t1 += dt;
	
	DrawLine(sx1, sy1, sx2, sy2, color);

	}
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1 / 40.0f;
	float t1 = 0;
	for (int i = 0; i < 40; i++)
	{
		int sx1, sy1;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);
		float t2 = t1 + dt;
		int sx2, sy2;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);

	}
}

void Framebuffer::DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1 / 40.0f;
	float t1 = 0;
	for (int i = 0; i < 40; i++)
	{
		int sx1, sy1;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);
		float t2 = t1 + dt;
		int sx2, sy2;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);

	}
}

void Framebuffer::DrawImage(int x, int y, const Image& image)
{
	if (x + image.m_width < 0 || x >= m_width || y + image.m_height < 0 || y >= m_height) return;

	for (int iy = 0; iy < image.m_height; iy++) 
	{
		int sy = y + iy;

		if (sy < 0 || sy >= m_height) continue;

		for (int ix = 0; ix < image.m_width; ix++)
		{
			int sx = x + ix;

			if (sx < 0 || sx >= m_width) continue;

			color_t color = image.m_buffer[ix + (iy * image.m_width)];

			//if (color.a == 0) continue;
			DrawPoint(sx, sy, color);

			//m_buffer[sx + sy * m_width] = color;
		}

	}
}




