#pragma once

#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <EmGine\SpriteBatch.h>
#include <EmGine\ResourceManager.h>
//#include <EmGine\TextureCache.h>

class Bullet{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void draw(EmGine::SpriteBatch& spriteBatch);
	bool update();

private:
	float m_speed;
	glm::vec2 m_direction,
		m_position;
	int m_lifeTime;
};

