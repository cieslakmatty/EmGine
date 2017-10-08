#include "Bullet.h"

#include "Agent.h"

Bullet::Bullet(std::string texturePath, glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	m_texturePath(texturePath),
	m_position(position),
	m_direction(direction),
	m_damage(damage),
	m_speed(speed) {

	m_color.r = 222;
	m_color.g = 222;
	m_color.b = 25;
	m_color.a = 255;
}

Bullet::~Bullet(){}

bool Bullet::update(float deltaTime, const std::vector<std::string> levelData){

	m_position += m_direction * m_speed * deltaTime;
	return collideWithWorld(levelData);
}

void Bullet::draw(EmGine::SpriteBatch& spriteBatch){

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x + BULLET_RADIUS, m_position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	spriteBatch.draw(destRect, uvRect, EmGine::ResourceManager::getTexture(m_texturePath).id, 0, m_color);
}

bool Bullet::collideWithAgent(Agent* agent){

	glm::vec2 centerPosA = m_position + glm::vec2(BULLET_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float collisionDepth = MIN_AGENT_BULLET_COLLISION_DISTANCE - distance;
	if (0 < collisionDepth){

		return true;
	}
	return false;
}

float Bullet::getDamage() const{

	return m_damage;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData){

	glm::ivec2 gridPos(floor(m_position.x / float(TILE_WIDTH)), floor(m_position.y / float(TILE_WIDTH)));

	if (gridPos.x < 0 || gridPos.x >= levelData[0].size() ||
		gridPos.y < 0 || gridPos.y >= levelData.size()){

		return true;
	}

	return ('.' != levelData[gridPos.y][gridPos.x] /*&& 'G' != levelData[gridPos.y][gridPos.x]*/);
}