#pragma once

#include <SDL/SDL_timer.h>

namespace EmGine{

class FrameLimiter{

public:
	static FrameLimiter* Instance();

	void setTargetFPS(unsigned int targetFPS);
	unsigned int getTargetFPS();
	void begin();
	void end();

private:
	FrameLimiter(){};
	FrameLimiter(FrameLimiter const&){};
	FrameLimiter& operator=(FrameLimiter const&){};

	static FrameLimiter* m_pInstance;

	unsigned int m_targetFPS;
	Uint32 m_startTicks;
};

}