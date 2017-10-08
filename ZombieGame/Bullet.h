#pragma once

#include <glm\vec2.hpp>
#include <vector>
#include <string>
#include <EmGine\SpriteBatch.h>
#include <EmGine\ResourceManager.h>

#include "Constants.h"

class Agent;
class Human;
class Zombie;

class Bullet{
public:
	Bullet(std::string texturePath, glm::vec2 position, glm::vec2 direction, float damage, float speed);
	~Bullet();

	bool update(float deltaTime, const std::vector<std::string> levelData);
	void draw(EmGine::SpriteBatch& spriteBatch);

	bool collideWithAgent(Agent* agent);

	float getDamage() const;
private:
	glm::vec2 m_position,
		m_direction;
	float m_speed,
		m_damage;
	std::string m_texturePath;
	EmGine::ColorRGBA8 m_color;

	bool collideWithWorld(const std::vector<std::string>& levelData);
};