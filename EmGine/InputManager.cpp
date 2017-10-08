#include "InputManager.h"

namespace EmGine{

InputManager::InputManager() :
	m_mouseCoords(0, 0){}

InputManager::~InputManager(){}

void InputManager::udpdate(){

	for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++){

		m_previousKeyMap[it->first] = it->second;
	}
}

void InputManager::pressKey(unsigned int keyID){

	m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID){

	m_keyMap[keyID] = false;
}


bool InputManager::isKeyDown(unsigned int keyID){

	auto it = m_keyMap.find(keyID);
	if (it != m_keyMap.end()){

		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID){

	if (isKeyDown(keyID) && !wasKeyDown(keyID)){

		return true;
	}
	return false;
}

void InputManager::setMouseCoords(float x, float y){

	m_mouseCoords = glm::vec2(x, y);
}

glm::vec2 InputManager::getMouseCoords() const {

	return m_mouseCoords;
}

bool InputManager::wasKeyDown(unsigned int keyID){

	auto it = m_previousKeyMap.find(keyID);
	if (it != m_previousKeyMap.end()){

		return it->second;
	}
	return false;
}

}