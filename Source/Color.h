#pragma once
#include "SDL.h"
using namespace std;

using color_t = SDL_Color;

enum class BlendMode
{
	Normal,
	Alpha,
	Additive,
	Multiply
};

 color_t ColorBlend(const color_t& src, const color_t& dest);
 color_t NormalBlend(const color_t& src, const color_t& dest);
 color_t AlphaBlend(const color_t& src, const color_t& dest);
 color_t AdditiveBlend(const color_t& src, const color_t& dest);
 void SetBlendMode(BlendMode blendmode);
 color_t ColorBlend(const color_t& src, const color_t& dest);

