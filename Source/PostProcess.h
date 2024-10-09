#pragma once
#include "FrameBuffer.h"
using namespace std;

namespace PostProcess 
{
	void Invert(vector<color_t>& buffer);
	void Monochrome(vector<color_t>& buffer);
	void Brightness(vector<color_t>& buffer, int brightness);

}