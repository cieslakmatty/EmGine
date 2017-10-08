#include "Agent.h"

#include "Human.h"
#include "Zombie.h"

Agent::Agent(){}

Agent::~Agent(){}

void Agent::init(glm::vec2 position, float speed, float health, std::string texturePath, EmGine::ColorRGBA8 color){

	m_position = position;
	m_speed = speed;
	m_texturePath = texturePath;
	m_color = color;
	m_health = health;
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData){

	std::vector<glm::vec2> collideTilePositions;
	checkTilePosition(levelData, collideTilePositions, glm::vec2(m_position.x, m_position.y));
	checkTilePosition(levelData, collideTilePositions, glm::vec2(m_position.x + AGENT_WIDTH, m_position.y));
	checkTilePosition(levelData, collideTilePositions, glm::vec2(m_position.x, m_position.y + AGENT_WIDTH));
	checkTilePosition(levelData, collideTilePositions, glm::vec2(m_position.x + AGENT_WIDTH, m_position.y + AGENT_WIDTH));

	if (0 == collideTilePositions.size()){

		return false;
	}

	for (unsigned int i = 0; i < collideTilePositions.size(); i++){

		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent){

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float collisionDepth = MIN_AGENT_COLLISION_DISTANCE - distance;
	if (0 < collisionDepth){

		glm::vec2 collicionDephVec = glm::normalize(distVec) * collisionDepth;

		m_position += collicionDephVec / 2.0f;
		agent->m_position -= collicionDephVec / 2.0f;
		return true;
	}
	return false;
}

void Agent::draw(EmGine::SpriteBatch& spriteBatch){

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	//glm::vec4 destRect(m_position.x - AGENT_SIZE / 2 , m_position.y - AGENT_SIZE / 2, m_position.x + AGENT_SIZE / 2, m_position.y + AGENT_SIZE / 2);
	glm::vec4 destRect(m_position.x, m_position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, EmGine::ResourceManager::getTexture(m_texturePath).id, 0, m_color);
}

bool Agent::applyDamage(float damage){

	m_health -= damage;
	if (0 > m_health){

		return true;
	}
	return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
							  std::vector<glm::vec2>& collideTilePositions, glm::vec2 pos){

	glm::vec2 gridPos = glm::vec2(floor(pos.x / (float)TILE_WIDTH),
									floor(pos.y / (float)TILE_WIDTH));
	//spawned outside of bounds
	if (gridPos.x < 0 || gridPos.x >= levelData[0].size() ||
		gridPos.y < 0 || gridPos.y >= levelData.size()){

		return;
	}
	if ('.' != levelData[gridPos.y][gridPos.x]){

		collideTilePositions.push_back(gridPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2, (float)TILE_WIDTH / 2));
	}
}

void Agent::collideWithTile(glm::vec2 tilePosition){

	glm::vec2 centerPos = m_position + glm::vec2(AGENT_RADIUS, AGENT_RADIUS);
	glm::vec2 distVec = centerPos -tilePosition;
	float xDepth = MIN_WALL_COLLISION_DISTANCE - abs(distVec.x);
	float yDepth = MIN_WALL_COLLISION_DISTANCE - abs(distVec.y);

	if (xDepth > 0 && yDepth > 0){

		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){

			if (distVec.x < 0){

				m_position.x -= xDepth;
			} else{

				m_position.x += xDepth;
			}
		} else{

			if (distVec.y < 0){

				m_position.y -= yDepth;
			} else{

				m_position.y += yDepth;
			}
		}
	}
}

glm::vec2 Agent::getPosition() const{

	return m_position;
}