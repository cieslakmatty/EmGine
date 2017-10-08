#include "MainGame.h"

#include "Level.h"
#include "Human.h"
#include "Player.h"
#include "Zombie.h"
#include "Gun.h"
#include "Bullet.h"

MainGame::MainGame() :
	m_screenWidth(1280),
	m_screenHeight(720),
	m_gameState(GameState::PLAY),
	m_currentLevel(-1),
	m_loadNextLevel(true),
	m_player(nullptr),
	m_numZombiesKilled(0),
	m_numHumansKilled(0){

	m_camera.init(m_screenWidth, m_screenHeight);
}

MainGame::~MainGame(){

	for (unsigned int i = 0; i < m_humans.size(); i++){

		delete m_humans[i];
	}
	for (unsigned int i = 0; i < m_zombies.size(); i++){

		delete m_zombies[i];
	}
}

void MainGame::run(){

	initSystems();
	gameLoop();
}

void MainGame::initSystems(){

	EmGine::init();
	m_window.createWindow("ZombieGame", m_screenWidth, m_screenHeight, 60, false, EmGine::WindowFlags::NONE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	initShaders();
	m_spriteBatch.init();
	loadLevels();
}

void MainGame::initShaders(){

	m_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}

void MainGame::loadLevels(){

	m_levels.push_back(Level("Levels/Level1.txt"));
}

void MainGame::checkVictory(){

	if (m_zombies.empty()){

		printf("Humans remaining: %i\n", m_humans.size());
		printf("Zombies killed: %i\n", m_numZombiesKilled);
		printf("Humans killed: %i\n", m_numHumansKilled);
		EmGine::fatalError("YOU WIN!");
	}
}

void MainGame::processInput(){

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)){

		switch (evnt.type){

		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_inputMan.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputMan.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputMan.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputMan.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_inputMan.setMouseCoords(evnt.motion.x, evnt.motion.y);
		}
	}
	if (m_inputMan.isKeyDown(SDLK_ESCAPE)){

		m_gameState = GameState::EXIT;
	}
}

void MainGame::gameLoop(){

	const int MAX_PHYSICS_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;
	Uint32 previousTicks = SDL_GetTicks();
	while (GameState::EXIT != m_gameState){

		EmGine::FrameLimiter::Instance()->begin();
		EmGine::FrameCounter::Instance()->update();
		Uint32 newTicks = SDL_GetTicks();
		Uint32 frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		Uint32 targetFPS = EmGine::FrameLimiter::Instance()->getTargetFPS();
		float totalDeltaTime = (float)frameTime / targetFPS;
		/*if (!targetFPS){
			totalDeltaTime = frameTime;

		} else{

			totalDeltaTime = frameTime / (1000.0f / targetFPS);
		}*/

		initLevel();
		m_inputMan.udpdate();
		processInput();
		m_camera.update();

		int i = 0;
		while (0.0f < totalDeltaTime && MAX_PHYSICS_STEPS > i){

			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			updateAgents(deltaTime);
			updateBullets(deltaTime);
			totalDeltaTime -= deltaTime;
			i++;
			//std::printf("deltaT: %f,\ttotalDeltaT: %f\ti:%i\n", deltaTime, totalDeltaTime, i);
		}

		checkVictory();

		m_camera.setPosition(m_player->getPosition());

		drawGame();

		/*print fps once every 10 frames*/
		static int frameCounter = 10;
		frameCounter--;
		if (!frameCounter){

			//std::cout << std::to_string(EmGine::FrameCounter::Instance()->getFPSAvg()) + "\n";
			std::printf("avg_fps: %f\tcur_fps: %f\n", EmGine::FrameCounter::Instance()->getFPSAvg(), EmGine::FrameCounter::Instance()->getFPS());
			frameCounter = 10;
		}
		EmGine::FrameLimiter::Instance()->end();
	}
}

void MainGame::updateAgents(float deltaTime){

	//update humans
	for (unsigned int i = 0; i < m_humans.size(); i++){

		m_humans[i]->update(deltaTime,
							m_levels[m_currentLevel].getLevelData(),
							m_humans,
							m_zombies);
	}

	//update zombies
	for (unsigned int i = 0; i < m_zombies.size(); i++){

		m_zombies[i]->update(deltaTime,
							 m_levels[m_currentLevel].getLevelData(),
							 m_humans,
							 m_zombies);
	}

	//zombie collisions
	for (unsigned int i = 0; i < m_zombies.size(); i++){
		//zombies with other zombies
		for (unsigned int j = i + 1; j < m_zombies.size(); j++){
			m_zombies[i]->collideWithAgent(m_zombies[j]);
		}
		//zombies with humans
		for (unsigned int j = 1; j < m_humans.size(); j++){
			if (m_zombies[i]->collideWithAgent(m_humans[j])){

				EmGine::ColorRGBA8 color(100, 255, 100, 255);
				m_zombies.push_back(new Zombie);
				m_zombies.back()->init(m_humans[j]->getPosition(), ZOMBIE_SPEED, ZOMBIE_HEALTH, "Textures/circle.png", color);
				delete m_humans[j];
				m_humans[j] = m_humans.back();
				m_humans.pop_back();
			}
		}
		//zombies with player
		if (m_zombies[i]->collideWithAgent(m_player)){
			printf("Humans remaining: %i\n", m_humans.size());
			printf("Zombies killed: %i\n", m_numZombiesKilled);
			printf("Humans killed: %i\n", m_numHumansKilled);
			EmGine::fatalError("GAME OVER");
		}
	}
	//human collisions
	for (unsigned int i = 0; i < m_humans.size(); i++){
		//humans with other humans
		for (unsigned int j = i + 1; j < m_humans.size(); j++){
			m_humans[i]->collideWithAgent(m_humans[j]);
		}
	}
}

void MainGame::updateBullets(float deltaTime){

	for (int i = 0; i < m_bullets.size();){

		if (m_bullets[i].update(deltaTime, m_levels[m_currentLevel].getLevelData())){

			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
		} else{

			i++;
		}
	}

	bool wasBulletRemoved;

	for (int i = 0; i < m_bullets.size(); i++){

		wasBulletRemoved = false;
		for (int j = 0; j < m_zombies.size();){

			if (m_bullets[i].collideWithAgent(m_zombies[j])){

				if (m_zombies[j]->applyDamage(m_bullets[i].getDamage())){

					delete m_zombies[j];
					m_zombies[j] = m_zombies.back();
					m_zombies.pop_back();
					m_numZombiesKilled++;
				} else{

					j++;
				}
				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
				wasBulletRemoved = true;
				i--;
				break;
			} else{

				j++;
			}
		}

		if (!wasBulletRemoved){
			for (int j = 1; j < m_humans.size();){

				if (m_bullets[i].collideWithAgent(m_humans[j])){

					if (m_humans[j]->applyDamage(m_bullets[i].getDamage())){

						delete m_humans[j];
						m_humans[j] = m_humans.back();
						m_humans.pop_back();
						m_numHumansKilled++;
					} else{

						j++;
					}
					m_bullets[i] = m_bullets.back();
					m_bullets.pop_back();
					wasBulletRemoved = true;
					i--;
					break;
				} else{

					j++;
				}
			}
		}
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

	m_levels[m_currentLevel].draw();
	m_spriteBatch.begin();
	
	//draw humans
	for (unsigned int i = 0; i < m_humans.size(); i++){

		m_humans[i]->draw(m_spriteBatch);
	}

	//draw zombies
	for (unsigned int i = 0; i < m_zombies.size(); i++){

		m_zombies[i]->draw(m_spriteBatch);
	}

	//draw bullets
	for (int i = 0; i < m_bullets.size(); i++){

		m_bullets[i].draw(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_colorProgram.unuse();

	m_window.swap();
}

void MainGame::initLevel(){

	if (!m_loadNextLevel){

		return;
	}

	m_currentLevel += 1;
	if (m_levels.size() == m_currentLevel){

		m_gameState = GameState::EXIT;
		return;
	} else{
		//delete old humans
		for (unsigned int i = 0; i < m_humans.size(); i++){

			delete m_humans[i];
		}
		if (m_currentLevel){

			m_levels[m_currentLevel - 1].unload();
		}

		m_player = new Player();
		m_humans.push_back(m_player);
		
		EmGine::ColorRGBA8 playerColor(255, 255, 255, 255);
		glm::vec2 playerPos = m_levels[m_currentLevel].load();
		m_player->init(playerPos, PLAYER_SPEED, "Textures/circle.png", playerColor, &m_inputMan, &m_camera, &m_bullets);

		std::mt19937 randomEngine;
		randomEngine.seed(time(nullptr));
		std::uniform_int_distribution<int> randX(2, m_levels[m_currentLevel].getLevelSize().x - 2);
		std::uniform_int_distribution<int> randY(2, m_levels[m_currentLevel].getLevelSize().y - 2);
		EmGine::ColorRGBA8 humanColor(0, 0, 200, 255);

		for (int i = 0; i < m_levels[m_currentLevel].getNumHumans(); i++){

			m_humans.push_back(new Human());
			m_humans.back()->init(glm::vec2(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH), HUMAN_SPEED, HUMAN_HEALTH, "Textures/circle.png", humanColor);
		}

		EmGine::ColorRGBA8 zombieColor(0, 200, 0, 255);

		const std::vector<glm::vec2> zombiePositions = m_levels[m_currentLevel].getZombiePositions();
		for (unsigned int i = 0; i < zombiePositions.size(); i++){

			m_zombies.push_back(new Zombie());
			m_zombies.back()->init(zombiePositions[i], ZOMBIE_SPEED, ZOMBIE_HEALTH, "Textures/circle.png", zombieColor);
		}

		//set up players guns
		m_player->addGun(new Gun("9mm Baretta", "Textures/circle.png",
								 PISTOL_FIRERATE, PISTOL_BULLETS_PER_SHOT, PISTOL_SPREAD, PISTOL_BULLET_SPEED, PISTOL_DAMAGE));
		m_player->addGun(new Gun("Double Barreled Shotgun", "Textures/circle.png",
								 SHOTGUN_FIRERATE, SHOTGUN_BULLETS_PER_SHOT, SHOTGUN_SPREAD, SHOTGUN_BULLET_SPEED, SHOTGUN_DAMAGE));
		m_player->addGun(new Gun("MP5", "Textures/circle.png",
								 MACHINEGUN_FIRERATE, MACHINEGUN_BULLETS_PER_SHOT, MACHINGUN_SPREAD, MACHINEGUN_BULLET_SPEED, MACHINEGUN_DAMAGE));

		m_loadNextLevel = false;
	}
}