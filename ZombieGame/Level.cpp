#include "Level.h"

#include "Human.h"
#include "Zombie.h"

Level::Level(const std::string& filenName):
	m_filePath(filenName){

	std::ifstream file;
	file.open(m_filePath);
	if (file.fail()){

		EmGine::fatalError("Failed to open: " + m_filePath);
	}
	std::string tmp;
	file >> tmp >> m_numHumans;

	std::getline(file, tmp);
	while (std::getline(file, tmp)){

		m_levelData.push_back(tmp);
	}
}

Level::~Level(){}

glm::vec2 Level::load(){

	

	glm::vec4 uvRect(0, 0, 1, 1);
	EmGine::ColorRGBA8 color(255, 255, 255, 255);
	glm::vec2 playerPos;
	m_spriteBatch.init();
	m_spriteBatch.begin();
	for (unsigned int y = 0; y < m_levelData.size(); y++){
		for (unsigned int x = 0; x < m_levelData[y].size(); x++){

			char tile = m_levelData[y][x];
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (tile){
			case 'R':
				m_spriteBatch.draw(destRect, uvRect,
								   EmGine::ResourceManager::getTexture("Textures/red_bricks.png").id,
								   0.0f, color);
				break;
			case 'G':
				m_spriteBatch.draw(destRect, uvRect,
								   EmGine::ResourceManager::getTexture("Textures/glass.png").id,
								   0.0f, color);
				break;
			case 'L':
				m_spriteBatch.draw(destRect, uvRect,
								   EmGine::ResourceManager::getTexture("Textures/light_bricks.png").id,
								   0.0f, color);
				break;
			case '@':
				playerPos = glm::ivec2(x * TILE_WIDTH, y * TILE_WIDTH);
				m_levelData[y][x] = '.';
				break;
			case'Z':
				m_zombiePositions.emplace_back(glm::ivec2(x * TILE_WIDTH, y * TILE_WIDTH));
				m_levelData[y][x] = '.';
			case '.':
				break;
			default :
				std::printf("Unexpected symbol in map data at: (%d, %d)\n", x, y);
			}
		}
	}
	m_spriteBatch.end();

	return playerPos;
}

void Level::unload(){

	m_levelData.clear();
	m_numHumans = 0;
	m_spriteBatch = EmGine::SpriteBatch();
	m_zombiePositions.clear();
}

void Level::draw(){

	m_spriteBatch.renderBatch();
}

const std::vector<std::string>& Level::getLevelData() const{

	return m_levelData;
}

const int Level::getNumHumans() const{

	return m_numHumans;
}

const glm::ivec2 Level::getLevelSize() const{

	return glm::ivec2(m_levelData[0].size(), m_levelData.size());
}

const std::vector<glm::vec2>& Level::getZombiePositions() const{

	return m_zombiePositions;
}