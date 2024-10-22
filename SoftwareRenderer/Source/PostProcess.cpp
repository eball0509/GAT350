#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm>


void PostProcess::Invert(vector<color_t>& buffer)
{
	for (auto& color : buffer)
	{
		color.r = 255 - color.r;
		color.g = 255 - color.g;
		color.b = 255 - color.b;
	}
}

void PostProcess::Monochrome(vector<color_t>& buffer)
{
	for (auto& color : buffer)
	{
		uint8_t average = static_cast<uint8_t>((color.r + color.g + color.b) / 3);

		color.r = average;
		color.g = average;
		color.b = average;
	}
}

void PostProcess::Brightness(vector<color_t>& buffer, int brightness)
{
	for (auto& color : buffer)
	{
		color.r = static_cast<uint8_t>(Clamp(color.r + brightness, 0, 255));
		color.g = static_cast<uint8_t>(Clamp(color.g + brightness, 0, 255));
		color.b = static_cast<uint8_t>(Clamp(color.b + brightness, 0, 255));
	}
}

void PostProcess::ColorBalance(vector<color_t>& buffer, int ro, int go, int bo)
{
	for (auto& color : buffer)
	{
		color.r = Clamp(color.r + ro, -255, 255);
		color.g = Clamp(color.g + go, -255, 255);
		color.b = Clamp(color.b + bo, -255, 255);
		
	}
}

void PostProcess::NoiseEffect(vector<color_t>& buffer, uint8_t noise)
{
	for (auto& color : buffer)
	{
		int offset = (rand() % ((noise * 2) + 1)) - noise;

		color.r = Clamp(color.r + offset, 0, 255);
		color.g = Clamp(color.g + offset, 0, 255);
		color.b = Clamp(color.b + offset, 0 ,255);
		
	}
}

void PostProcess::Threshold(vector<color_t>& buffer, uint8_t threshold)
{
	for (auto& color : buffer)
	{
		if (color.r > threshold || color.g > threshold || color.b > threshold)
		{
			color.r = 255, 255, 255;
			color.g = 255, 255, 255;
			color.b = 255, 255, 255;
		}
		else
		{
			color.r = 0, 0, 0;
			color.g = 0, 0, 0;
			color.b = 0, 0, 0;
		}
	}
}

void PostProcess::Posterization(vector<color_t>& buffer, uint8_t levels)
{
	uint8_t level = 255 / levels ;
	for (auto& color : buffer)
	{
		color.r = round(color.r / level) * level;
		color.g = round(color.g / level) * level;
		color.b = round(color.b / level) * level;
	}
}

void PostProcess::Alpha(vector<color_t>& buffer, uint8_t alpha)
{
	for_each(buffer.begin(), buffer.end(), [alpha](color_t& c)
		{
			c.a = alpha;
		});
}

void PostProcess::BoxBlur(std::vector<color_t>& buffer, int width, int height)
{
	vector<color_t> source = buffer;

	int k[3][3] =
	{
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		int x = i % width;
		int y = i / width;


		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 9);
		color.g = static_cast<uint8_t>(g / 9);
		color.b = static_cast<uint8_t>(b / 9);
	}
}

void PostProcess::GaussianBlur(std::vector<color_t>& buffer, int width, int height)
{
	vector<color_t> source = buffer;

	int k[3][3] =
	{
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		int x = i % width;
		int y = i / width;


		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 16);
		color.g = static_cast<uint8_t>(g / 16);
		color.b = static_cast<uint8_t>(b / 16);
	}
}

void PostProcess::Sharpen(std::vector<color_t>& buffer, int width, int height)
{
	vector<color_t> source = buffer;

	int k[3][3] =
	{
		{1, 2, 1},
		{2, 4, 1},
		{1, 2, 1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		int x = i % width;
		int y = i / width;


		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(Clamp(r, 0, 255));
		color.r = static_cast<uint8_t>(Clamp(g, 0, 255));
		color.r = static_cast<uint8_t>(Clamp(b, 0, 255));
	}
}

void PostProcess::Edge(std::vector<color_t>& buffer, int width, int height, int threshold)
{
	vector<color_t> source = buffer;

	int hk[3][3] =
	{
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	};

	int vk[3][3] =
	{
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		int x = i % width;
		int y = i / width;



		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;
		int h = 0, v = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				h += pixel.r * hk[iy][ix];
				v += pixel.r * vk[iy][ix];
			}
		}

		int m = static_cast<int>(sqrt((h * h) + (v * v)));
		m = (m > threshold) ? m : 0;

		uint8_t c = Clamp(m, 0, 255);

		color_t& color = buffer[i];
		color.r = c;
		color.g = c;
		color.b = c;

	}
}

void PostProcess::Emboss(std::vector<color_t>& buffer, int width, int height)
{
	vector<color_t> source = buffer;

	int k[3][3] =
	{
		{-2, -1, 0},
		{-1, 1, 1},
		{0, 1, 2}
	};

	for (int i = 0; i < buffer.size(); i++)
	{
		int x = i % width;
		int y = i / width;


		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix];

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(Clamp(r, 0, 255));
		color.g = static_cast<uint8_t>(Clamp(g, 0, 255));
		color.b = static_cast<uint8_t>(Clamp(b, 0, 255));
	}
}

