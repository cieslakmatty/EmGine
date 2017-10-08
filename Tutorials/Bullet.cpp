#include "Bullet.h"

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) :
	m_position(pos),
	m_direction(dir),
	m_speed(speed),
	m_lifeTime(lifeTime){
}

Bullet::~Bullet(){}

void Bullet::draw(EmGine::SpriteBatch& spriteBatch){

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static EmGine::GLTexture tex = EmGine::ResourceManager::getTexture("Textures/Items/fireball.png");
	EmGine::ColorRGBA8 color(255, 255, 255, 255);
	glm::vec4 destRect(m_position.x - tex.width / 2, m_position.y - tex.height / 2, tex.width, tex.height);
	spriteBatch.draw(destRect, uv, tex.id, 0, color);
}

bool Bullet::update(){

	m_position += m_direction * m_speed;
	m_lifeTime--;
	if (!m_lifeTime){

		return true;
	}
	return false;
}