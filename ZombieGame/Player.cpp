#include "Player.h"

#include "Zombie.h"
#include "Gun.h"
#include "Bullet.h"

Player::Player() :
	Human(),
	m_currentGunIndex(-1) {}

Player::~Player(){

	for (unsigned int i = 0; i < m_guns.size(); i++){

		delete m_guns[i];
	}
}

void Player::init(glm::vec2 position,
				  float speed,
				  std::string texturePath,
				  EmGine::ColorRGBA8 color,
				  EmGine::InputManager* inputMan,
				  EmGine::Camera2D* camera,
				  std::vector<Bullet>* bullets){

	m_position = position;
	m_speed = speed;
	m_texturePath = texturePath;
	m_color = color;
	m_inputMan = inputMan;
	m_camera = camera;
	m_bullets = bullets;
}

void Player::update(float deltaTime,
					const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies){

	//movement
	if (m_inputMan->isKeyDown(SDLK_w)){

		m_position.y += m_speed * deltaTime;
	} else if (m_inputMan->isKeyDown(SDLK_s)){

		m_position.y -= m_speed * deltaTime;
	}
	if (m_inputMan->isKeyDown(SDLK_d)){

		m_position.x += m_speed * deltaTime;
	} else if (m_inputMan->isKeyDown(SDLK_a)){

		m_position.x -= m_speed * deltaTime;
	}
	//guns
	if (m_inputMan->isKeyDown(SDLK_1) && m_guns.size() >= 0){

		m_currentGunIndex = 0;
	} else if (m_inputMan->isKeyDown(SDLK_2) && m_guns.size() >= 1){

		m_currentGunIndex = 1;
	} else if (m_inputMan->isKeyDown(SDLK_3) && m_guns.size() >= 2){

		m_currentGunIndex = 2;
	}

	if (-1 != m_currentGunIndex){

		glm::vec2 mousePosition = m_camera->convertScreenToWorld(m_inputMan->getMouseCoords());
		glm::vec2 playerCenterPos = m_position + glm::vec2(AGENT_RADIUS);
		glm::vec2 playerDirection = glm::normalize(mousePosition - playerCenterPos);
		m_guns[m_currentGunIndex]->update(deltaTime, m_inputMan->isKeyDown(SDL_BUTTON_LEFT), playerCenterPos, playerDirection, m_bullets);
	}
	collideWithLevel(levelData);
}

void Player::addGun(Gun* gun){

	m_guns.push_back(gun);

	//if not gun equipped. equip gun.
	if (-1 == m_currentGunIndex){

		m_currentGunIndex = 0;
	}
}