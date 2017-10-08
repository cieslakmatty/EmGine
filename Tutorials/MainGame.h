#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <EmGine\EnGine.h>
#include <EmGine\Window.h>
#include <EmGine\MyErrors.h>
#include <EmGine\FrameCounter.h>
#include <EmGine\FrameLimiter.h>
#include <EmGine\Camera2D.h>
#include <EmGine\InputManager.h>

//temp
#include <iostream>
#include <vector>
#include <EmGine\ResourceManager.h>
#include <EmGine\GLSLProgram.h>
#include <EmGine\SpriteBatch.h>
#include "Bullet.h"


enum class GameState{PLAY, MENU, EXIT};

class MainGame{

public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void processInput();
	void gameLoop();
	void drawGame();

	EmGine::Window m_window;
	EmGine::Camera2D m_camera;
	int m_screenWidth,
		m_screenHeight;
	GameState m_gameState;
	EmGine::SpriteBatch m_spriteBatch;
	EmGine::GLSLProgram m_colorProgram;
	EmGine::InputManager m_inputManager;

	std::vector<Bullet> m_bullets;
};