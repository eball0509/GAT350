#pragma once
#include <SDL.h>
#include <string>
class Renderer
{
public:
	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string name, int height, int width);
	void BeginFrame();
	void EndFrame();

	void CheckForEvents();
	void CopyFramebuffer(const class Framebuffer& framebuffer);

	void operator =(const Framebuffer& framebuffer);

	bool IsQuit() { return quit; }
	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

	friend class Framebuffer;

public:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	int m_width = 0;
	int m_height = 0;
	bool quit = false;
};