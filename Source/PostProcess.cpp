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

