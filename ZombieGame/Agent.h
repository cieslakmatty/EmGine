#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <glm\vec2.hpp>
#include <EmGine\SpriteBatch.h>
#include <EmGine\ResourceManager.h>

#include "Constants.h"

class Zombie;
class Human;

class Agent{
public:
	Agent();
	virtual ~Agent();

	void init(glm::vec2 position, float speed, float health, std::string texturePath, EmGine::ColorRGBA8 color);
	virtual void update(float deltaTime,
						const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;
	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithAgent(Agent* agent);
	void draw(EmGine::SpriteBatch& spriteBatch);
	bool applyDamage(float damage);

	glm::vec2 getPosition() const;

protected:
	void checkTilePosition(const std::vector<std::string>& levelData,
						   std::vector<glm::vec2>& collideTilePositions, glm::vec2 pos);
	void collideWithTile(glm::vec2 tilePosition);

	glm::vec2 m_position;
	float m_speed;
	float m_health;
	std::string m_texturePath;
	EmGine::ColorRGBA8 m_color;
};

