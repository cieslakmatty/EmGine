#include "FrameLimiter.h"

#include "FrameCounter.h"

namespace EmGine{

FrameLimiter* FrameLimiter::m_pInstance = NULL;

FrameLimiter* FrameLimiter::Instance(){

	if (!m_pInstance){

		m_pInstance = new FrameLimiter;
	}
	return m_pInstance;
}

void FrameLimiter::setTargetFPS(unsigned int targetFPS){

	//set to 0 to disable
	m_targetFPS = targetFPS;
}

unsigned int FrameLimiter::getTargetFPS(){

	return m_targetFPS;
}

void FrameLimiter::begin(){

	if (!m_targetFPS){

		return;
	}
	m_startTicks = SDL_GetTicks();
}

void FrameLimiter::end(){

	if (!m_targetFPS){

		return;
	}
	Uint32 frameTime = SDL_GetTicks() - m_startTicks;
	if (1000.0f / m_targetFPS > frameTime){

		SDL_Delay(Uint32(1000.0f / m_targetFPS) - frameTime);
	}
}

}