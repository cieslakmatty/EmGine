#pragma once

#include <EmGine\InputManager.h>
#include <EmGine\Camera2D.h>

#include "Human.h"

class Zombie;
class Gun;
class Bullet;

class Player :
	public Human{
public:
	Player();
	~Player();

	void init(glm::vec2 position,
			  float speed,
			  std::string texturePath,
			  EmGine::ColorRGBA8 color,
			  EmGine::InputManager* inputMan,
			  EmGine::Camera2D* camera,
			  std::vector<Bullet>* bullets);
	void update(float deltaTime,
				const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies) override;
	void addGun(Gun* gun);

private:
	EmGine::InputManager* m_inputMan;
	EmGine::Camera2D* m_camera;
	std::vector<Gun*> m_guns;
	std::vector<Bullet>* m_bullets;
	int m_currentGunIndex;
};

