#pragma once
#include "FrameBuffer.h"
#include <iostream>
#include <SDL.h>
#include <string>
using namespace std;

class Renderer {

public:
	void Initialize();

	void CreateWindow(string name, int width, int height);

	void CopyFrameBuffer( const Framebuffer framebuffer);

	void operator = (const class Framebuffer& framebuffer);

	friend class FrameBuffer;
public:

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

};


