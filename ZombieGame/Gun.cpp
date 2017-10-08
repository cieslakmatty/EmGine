#include "Gun.h"

Gun::Gun(std::string name, std::string bulletTexturePath, int fireRate, int bulletsPerShot, float spread, int bulletSpeed, float bulletDamage) :
	m_name(name),
	m_bulletTexturePath(bulletTexturePath),
	m_fireRate(fireRate),
	m_bulletsPerShot(bulletsPerShot),
	m_spread(spread),
	m_bulletSpeed(bulletSpeed),
	m_bulletDamage(bulletDamage),
	m_frameCounter(0){
}

Gun::~Gun(){}

void Gun::update(float deltaTime, bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>* bullets){

	m_frameCounter += deltaTime;
	if (m_frameCounter > m_fireRate && isMouseDown){

		fire(position, direction, bullets);
		m_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>* bullets){

	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randRotate(-m_spread, m_spread);

	for (int i = 0; i < m_bulletsPerShot; i++){

		bullets->emplace_back(m_bulletTexturePath, position, glm::rotate(direction, glm::radians(randRotate(randomEngine))), m_bulletDamage, m_bulletSpeed);
	}
}