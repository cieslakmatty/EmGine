#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <glm\vec2.hpp>
#include <EmGine\MyErrors.h>
#include <EmGine\SpriteBatch.h>
#include <EmGine\GLTexture.h>
#include <EmGine\ResourceManager.h>
#include <EmGine\Vertex.h>

#include "Constants.h"

class Human;
class Zombie;

class Level{
public:
	Level(const std::string& filenName);
	~Level();

	glm::vec2 load();
	void unload();
	void draw();
	const std::vector<std::string>& getLevelData() const;
	const int getNumHumans() const;
	const glm::ivec2 getLevelSize() const;
	const std::vector<glm::vec2>& getZombiePositions() const;

private:
	std::vector<std::string> m_levelData;
	int m_numHumans;
	std::string m_filePath;
	EmGine::SpriteBatch m_spriteBatch;
	std::vector<glm::vec2> m_zombiePositions;
};

