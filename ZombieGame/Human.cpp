#include "Human.h"

Human::Human(){}

Human::~Human(){}

void Human::init(glm::vec2 position, float speed, float health, std::string texturePath, EmGine::ColorRGBA8 color) {

	m_position = position;
	m_speed = speed;
	m_texturePath = texturePath;
	m_color = color;
	m_health = health;

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);
	m_direction = glm::vec2(0.0f, 0.0f);
	while (0 == glm::length(m_direction)){

		m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	}
	m_direction = glm::normalize(m_direction);
	m_frames = 0;
}

void Human::update(float deltaTime,
				   const std::vector<std::string>& levelData,
				   std::vector<Human*>& humans,
				   std::vector<Zombie*>& zombies){

	m_position += m_direction * m_speed * deltaTime;

	if (collideWithLevel(levelData) || m_frames % 50){

		static std::mt19937 randomEngine(time(nullptr));
		static std::uniform_real_distribution<float> randRotation(-40.f, 40.f);
		m_direction = glm::rotate(m_direction, glm::radians(randRotation(randomEngine)));
	}
	m_frames++;
}