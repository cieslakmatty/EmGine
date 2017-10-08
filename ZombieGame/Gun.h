#pragma once

#include <string>
#include <vector>
#include <glm\vec2.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <random>
#include <ctime>

#include "Bullet.h"

class Gun{
public:
	Gun(std::string name, std::string bulletTexturePath, int fireRate, int bulletsPerShot, float spread, int bulletSpeed, float bulletDamage);
	~Gun();

	void update(float deltaTime, bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>* bullets);

private:
	std::string m_name,
		m_bulletTexturePath;
	int m_fireRate,
		m_bulletsPerShot,
		m_bulletSpeed;
	float m_spread,
		m_bulletDamage;

	float m_frameCounter;

	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>* bullets);
};