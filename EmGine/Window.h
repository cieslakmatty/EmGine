#pragma once

#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "MyErrors.h"
#include "FrameCounter.h"
#include "FrameLimiter.h"

namespace EmGine{

enum WindowFlags{
	NONE = 0,
	FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	INVISIBLE = SDL_WINDOW_HIDDEN,
	BORDERLESS = SDL_WINDOW_BORDERLESS,
	RESIZEABLE = SDL_WINDOW_RESIZABLE,
	MINIMIZED = SDL_WINDOW_MINIMIZED,
	MAXIMIZED = SDL_WINDOW_MAXIMIZED,
	INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
	INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
	MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
	MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
};

class Window{
public:
	Window();
	~Window();

	int createWindow(std::string windowName, int screenWidth, int screenHeight, Uint32 targetFPS, bool VSyncON, WindowFlags flags);
	void swap();

	int getScreenWidth();
	int getScreenHeight();
private:
	SDL_Window* m_window;
	int m_screenWidth,
		m_screenHeight;
};

}