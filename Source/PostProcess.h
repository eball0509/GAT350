#pragma once
#include "FrameBuffer.h"
using namespace std;

namespace PostProcess 
{
	void Invert(vector<color_t>& buffer);
	void Monochrome(vector<color_t>& buffer);
	void Brightness(vector<color_t>& buffer, int brightness);
	void ColorBalance(vector<color_t>& buffer, int ro, int go, int bo );
	void NoiseEffect(vector<color_t>& buffer, uint8_t noise );
	void Threshold(vector<color_t>& buffer, uint8_t threshold );
	void Posterization(vector<color_t>& buffer, uint8_t levels );

}