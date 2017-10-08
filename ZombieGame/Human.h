#pragma once

#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

#include "Agent.h"

class Human :
	public Agent{
public:
	Human();
	virtual ~Human();
	void init(glm::vec2 position, float speed, float health, std::string texturePath, EmGine::ColorRGBA8 color);

	virtual void update(float deltaTime,
						const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies) override;

private:
	glm::vec2 m_direction;
	int m_frames;
};

