#include "Window.h"

namespace EmGine{

Window::Window() :
	m_window(nullptr){
}

Window::~Window(){}

int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, Uint32 targetFPS, bool VSyncON, WindowFlags flags){

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								m_screenWidth, m_screenHeight, flags | SDL_WINDOW_OPENGL);
	if (nullptr == m_window){

		fatalError("SDL_Window could not be created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (nullptr == glContext){

		fatalError("SDL_GLContext could not be created");
	}

	GLenum error = glewInit();
	if (GLEW_OK != error){

		fatalError("Could not initialise glew");
	}

	std::printf("***	OPENGL VERSION: %s	***\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.2f, 1.0);

	SDL_GL_SetSwapInterval(VSyncON);

	FrameCounter::Instance()->setNumberofSamples(100);
	FrameLimiter::Instance()->setTargetFPS(targetFPS);

	//enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Window::swap(){

	SDL_GL_SwapWindow(m_window);
}

int Window::getScreenWidth(){

	return m_screenWidth;
}

int Window::getScreenHeight(){

	return m_screenHeight;
}

}