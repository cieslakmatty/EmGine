#pragma once

#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <EmGine\EnGine.h>
#include <EmGine\Window.h>
#include <EmGine\Camera2D.h>
#include <EmGine\SpriteBatch.h>
#include <EmGine\GLSLProgram.h>
#include <EmGine\InputManager.h>


class Player;
class Human;
class Zombie;
class Gun;
class Level;
class Bullet;

enum class GameState{ PLAY, MENU, EXIT };

class MainGame{

public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void loadLevels();
	void checkVictory();
	void processInput();
	void gameLoop();
	void updateAgents(float deltaTime);
	void updateBullets(float deltaTime);
	void drawGame();
	void initLevel();

	EmGine::Window m_window;
	EmGine::Camera2D m_camera;
	int m_screenWidth,
		m_screenHeight;
	GameState m_gameState;
	EmGine::SpriteBatch m_spriteBatch;
	EmGine::GLSLProgram m_colorProgram;
	EmGine::InputManager m_inputMan;

	std::vector<Level> m_levels;
	int m_currentLevel;
	bool m_loadNextLevel;

	Player* m_player;
	std::vector<Human *> m_humans;
	std::vector<Zombie*> m_zombies;
	std::vector<Bullet> m_bullets;

	int m_numZombiesKilled;
	int m_numHumansKilled;
};