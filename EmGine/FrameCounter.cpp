#include "FrameCounter.h"

namespace EmGine{

FrameCounter* FrameCounter::m_pInstance = NULL;

FrameCounter* FrameCounter::Instance(){

	if (!m_pInstance){

		m_pInstance = new FrameCounter();
	}
	return m_pInstance;
}

FrameCounter::FrameCounter() :
	m_fpsAverage(-1.0f),
	m_fps(-1.0f){

	//set a default
	setNumberofSamples(100);
	m_previousTicks = SDL_GetTicks();
}

void FrameCounter::update(){

	float currentTicks = SDL_GetTicks();
	m_frameTime = currentTicks - m_previousTicks;

	m_frameTimes.push_back(m_frameTime);
	//if there are more than m_numSamples samples remove the one at the front
	if (m_numSamples < m_frameTimes.size()){

		m_frameTimes.erase(m_frameTimes.begin());
	}
	//calc the average fram time
	for (unsigned int i = 0; i < m_frameTimes.size(); i++){

		m_frameTimeAverage += m_frameTimes[i];
	}
	m_frameTimeAverage /= m_frameTimes.size();
	//Average FPS
	if (0 < m_frameTimeAverage){

		m_fpsAverage = 1000 / m_frameTimeAverage;
	} else{

		m_fpsAverage = 0;
	}
	//FPS
	if (0 < m_frameTime){

		m_fps = 1000 / m_frameTime;
	} else{

		m_fps = 0;
	}
	m_previousTicks = currentTicks;
}
float FrameCounter::getFPS(){

	return m_fps;
}

float FrameCounter::getFPSAvg(){

	return m_fpsAverage;
}

void FrameCounter::setNumberofSamples(unsigned int numSamples){

	m_numSamples = numSamples;
}
}