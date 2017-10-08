#pragma once

#include "Agent.h"
#include "Human.h"

class Zombie :
	public Agent{
public:
	Zombie();
	~Zombie();

	void update(float deltaTime,
				const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies) override;

private:
	const Human* getNearestHuman(std::vector<Human*>& humans) const;
};

