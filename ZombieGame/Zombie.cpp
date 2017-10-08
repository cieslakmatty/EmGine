#include "Zombie.h"

Zombie::Zombie(){}

Zombie::~Zombie(){}

void Zombie::update(float deltaTime,
					const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies){

	const Human* closestHuman = getNearestHuman(humans);
	if (nullptr != closestHuman){

		glm::vec2 direction = glm::normalize(closestHuman->getPosition() - m_position);
		m_position += direction * m_speed * deltaTime;
	}
	collideWithLevel(levelData);
}

const Human* Zombie::getNearestHuman(std::vector<Human*>& humans) const{

	Human* closestHuman = nullptr;
	float smallestDistance = std::numeric_limits<float>::max();

	for (unsigned int i = 0; i < humans.size(); i++){

		glm::vec2 distVec = humans[i]->getPosition() - m_position;
		float distance = glm::length(distVec);
		if (distance < smallestDistance){
			 
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;
}