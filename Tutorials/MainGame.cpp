#include "MainGame.h"

MainGame::MainGame(){
	m_screenWidth = 1280;
	m_screenHeight = 720;
	m_gameState = GameState::PLAY;
	m_camera.init(m_screenWidth, m_screenHeight);
}

MainGame::~MainGame(){}

void MainGame::initSystems(){

	EmGine::init();
	m_window.createWindow("Tutorial", m_screenWidth, m_screenHeight, 60, false, EmGine::WindowFlags::NONE);

	initShaders();
	m_spriteBatch.init();
}

void MainGame::initShaders(){

	m_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}

void MainGame::run(){

	initSystems();
	gameLoop();
}

void MainGame::processInput(){

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)){

		switch (evnt.type){

		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
		}
	}
	if (m_inputManager.isKeyDown(SDLK_ESCAPE)){

		m_gameState = GameState::EXIT;
	}
	if (m_inputManager.isKeyDown(SDLK_w)){

		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, 1.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_s)){

		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -1.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_a)){

		m_camera.setPosition(m_camera.getPosition() + glm::vec2(-1.0f, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_d)){

		m_camera.setPosition(m_camera.getPosition() + glm::vec2(1.0f, 0.0f));
	}
	if (m_inputManager.isKeyDown(SDLK_q)){

		m_camera.setScale(m_camera.getScale() + 0.1);
	}
	if (m_inputManager.isKeyDown(SDLK_e)){

		m_camera.setScale(m_camera.getScale() - 0.1);
	}
	if (m_inputManager.isKeyDown(SDL_BUTTON_LEFT)){

		glm::vec2 mouseWorldPos = m_camera.convertScreenToWorld(m_inputManager.getMouseCoords());
		glm::vec2 playerPos(0, 0);
		glm::vec2 direction = mouseWorldPos - playerPos;
		direction = glm::normalize(direction);
		m_bullets.emplace_back(playerPos, direction, 5.0f, 100);
	}
}

void MainGame::drawGame(){

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = m_colorProgram.getUniformLocation("P");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(m_camera.getCameraMatrix()[0][0]));

	m_spriteBatch.begin();
	static EmGine::GLTexture tex = EmGine::ResourceManager::getTexture("Textures/Player/p1_stand.png");
	glm::vec4 position0(0.0f - tex.width / 2, 0.0f - tex.height / 2, tex.width, tex.height);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	EmGine::ColorRGBA8 color(255, 255, 255, 255);
	m_spriteBatch.draw(position0, uv, tex.id, 0, color);

	for (int i = 0; i < m_bullets.size(); i++){

		m_bullets[i].draw(m_spriteBatch);
	}
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_colorProgram.unuse();

	m_window.swap();
}

void MainGame::gameLoop(){

	while (GameState::EXIT != m_gameState){

		EmGine::FrameLimiter::Instance()->begin();
		processInput();
		m_camera.update();

		for (int i = 0; i < m_bullets.size();){

			if (m_bullets[i].update()){

				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
			}
			else{

				i++;
			}
		}

		drawGame();

		EmGine::FrameCounter::Instance()->update();
		/*print fps once every 10 frames*/
		static int frameCounter = 10;
		frameCounter--;
		if (!frameCounter){

			std::cout << std::to_string(EmGine::FrameCounter::Instance()->getFPSAvg()) + "\n";
			frameCounter = 10;
		}
		EmGine::FrameLimiter::Instance()->end();
	}
}