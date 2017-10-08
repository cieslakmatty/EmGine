#pragma once

#include <vector>
#include<SDL/SDL_timer.h>

namespace EmGine{

class FrameCounter{
public:
	static FrameCounter* Instance();
	void update();
	float getFPS();
	float getFPSAvg();
	void setNumberofSamples(unsigned int numSamples);

private:
	FrameCounter();
	FrameCounter(FrameCounter const&){};
	FrameCounter& operator=(FrameCounter const&){};

	static FrameCounter* m_pInstance;

	float m_previousTicks;
	unsigned int m_numSamples;
	float m_fps;
	float m_fpsAverage;
	float m_frameTime;
	float m_frameTimeAverage;
	std::vector<float> m_frameTimes;
};

}