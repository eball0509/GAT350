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

