#include "stdafx.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->checkHome = false;
	this->playerDieSound = true;
	this->gameOverSound = true;

	this->selectPause = true;

	this->gameOver = false;

	this->countReward = this->tileMap->getRewardLeft();

	curser.loadFromSystem(sf::Cursor::Cross);
	window->setMouseCursor(curser);
	pcurser.loadFromSystem(sf::Cursor::Arrow);
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 
			0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Initializer functions
void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width ),
			static_cast<float>(this->stateData->gfxSettings->resolution.height  )
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	if(!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}

	if (!this->textures["BIRD1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/bird1_61x57.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["BLOB_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/blob1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["SCORPION_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/scorpion1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
	if (!this->textures["SPIDER_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/spider1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("RESUME", gui::p2pY(34.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Resume");
	this->pmenu->addButton("RESTART", gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Restart");
	
}
void GameState::initGameOverMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->gmenu = new GameOverMenu(this->stateData->gfxSettings->resolution, this->font);

	this->gmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	this->gmenu->addButton("RETRY", gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Retry");
	
}
void GameState::initLevelCompletedMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->lmenu = new LevelCompletedMenu(this->stateData->gfxSettings->resolution, this->font);

	this->lmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	this->lmenu->addButton("NEXT", gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Next Level");
	
	//Game end menu
	this->emenu = new GameEndMenu(this->stateData->gfxSettings->resolution, this->font);

	this->emenu->addButton("QUIT", gui::p2pY(64.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");

	
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();

}

void GameState::initDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}

void GameState::initPlayers()
{
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"], this->countStage);
}

void GameState::initPlayerGUI()
{
	
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
	
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initTileMap()
{
	std::stringstream ss;
	ss << "Map" << this->countStage << ".slmp";
	this->tileMap = new TileMap(ss.str());

}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/PixellettersFull.ttf");
}

void GameState::initAudio()
{
	
	if (!music.openFromFile("Resources/Audios/Background.wav"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD MUSIC." << "\n";
	}
	music.setLoop(true);
	music.setVolume(30);
	music.play();
	
}

//Constructors / Destructors
GameState::GameState(StateData* state_data, int map_no)
	: State(state_data)
{
	
	this->countStage = map_no;
	
	
	
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initGameOverMenu();
	this->initLevelCompletedMenu();
	this->initShaders();
	this->initKeyTime();
	this->initDebugText();

	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();
	this->initAudio();
	this->initVariables();

	
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->gmenu;
	delete this->lmenu;
	delete this->emenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
	
	curser.loadFromSystem(sf::Cursor::Arrow);
	window->setMouseCursor(curser);
}

const bool GameState::getKeyTime()
{	
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;	
}





//Functions
void GameState::updateView(const float & dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);
	
	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && !this->gameOver && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}
}

void GameState::updatePlayerGUI(const float & dt)
{
	this->playerGUI->update(dt);

}

void GameState::updateToggle()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB_CHARACTER"))) && this->getKeyTime())
	{
		this->playerGUI->toggleCharacterTab();
		if (!this->selectPause)
			this->selectPause = true;
		else
			this->selectPause = false;
	}
	
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pmenu->isButtonPressed("RESUME"))
		this->unpauseState();
	if (this->pmenu->isButtonPressed("RESTART"))
	{
		delete this->pmenu;
		delete this->player;
		delete this->playerGUI;
		delete this->enemySystem;
		delete this->tileMap;
		delete this->tts;

		for (size_t i = 0; i < this->activeEnemies.size(); i++)
		{
			delete this->activeEnemies[i];
		}
		this->activeEnemies.clear();
		
		
		this->initDeferredRender();
		this->initView();
		this->initKeybinds();
		this->initFonts();
		this->initTextures();
		this->initPauseMenu();
		this->initShaders();
		this->initKeyTime();
		this->initDebugText();

		this->initPlayers();
		this->initPlayerGUI();
		this->initEnemySystem();
		this->initTileMap();
		this->initSystems();

		this->unpauseState();
		this->initVariables();

	}
}
void GameState::updateGameOverMenuButtons()
{
	if (this->gmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->gmenu->isButtonPressed("RETRY"))
	{
		delete this->pmenu;
		delete this->gmenu;
		delete this->lmenu;
		delete this->emenu;
		delete this->player;
		delete this->playerGUI;
		delete this->enemySystem;
		delete this->tileMap;
		delete this->tts;

		for (size_t i = 0; i < this->activeEnemies.size(); i++)
		{
			delete this->activeEnemies[i];
		}
		this->activeEnemies.clear();
		
		

	
		this->initDeferredRender();
		this->initView();
		this->initKeybinds();
		this->initFonts();
		this->initTextures();
		this->initPauseMenu();
		this->initGameOverMenu();
		this->initLevelCompletedMenu();
		this->initShaders();
		this->initKeyTime();
		this->initDebugText();

		this->initPlayers();
		this->initPlayerGUI();
		this->initEnemySystem();
		this->initTileMap();
		this->initSystems();
		this->initAudio();
		this->initVariables();
	}
}
void GameState::updateLevelCompletedMenuButtons()
{
	if (this->countStage == 15)
	{
		this->emenu->update(this->mousePosWindow);

		if (this->emenu->isButtonPressed("QUIT"))
			this->endState();
	}
	else
	{
		this->lmenu->update(this->mousePosWindow);
		if (this->lmenu->isButtonPressed("QUIT"))
			this->endState();

		if (this->lmenu->isButtonPressed("NEXT"))
		{
			delete this->pmenu;
			delete this->gmenu;
			delete this->lmenu;
			delete this->emenu;
			delete this->player;
			delete this->playerGUI;
			delete this->enemySystem;
			delete this->tileMap;
			delete this->tts;

			for (size_t i = 0; i < this->activeEnemies.size(); i++)
			{
				delete this->activeEnemies[i];
			}
			this->activeEnemies.clear();

			++this->countStage;

			this->initDeferredRender();
			this->initView();
			this->initKeybinds();
			this->initFonts();
			this->initTextures();
			this->initPauseMenu();
			this->initGameOverMenu();
			this->initLevelCompletedMenu();
			this->initShaders();
			this->initKeyTime();
			this->initDebugText();

			this->initPlayers();
			this->initPlayerGUI();
			this->initEnemySystem();
			this->initTileMap();
			this->initSystems();
			this->initAudio();
			this->initVariables();
		}
	}
}

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt); 
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float & dt)
{
	this->player->update(dt, this->mousePosView, this->view);
}

void GameState::updateCombatAndEnemies(const float& dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BLAST")))
		&& this->player->getEXP() >= 100
		&& getKeyTime())
	{
		jump:
		unsigned index = 0;
		for (auto* enemy : this->activeEnemies)
		{
			if (
				this->player->getCircleBound().intersects(enemy->getGlobalBounds())
				)
			{
				if (enemy->getAttributeComponent()->getRewardStatus()
					&& enemy->getSpriteDistance(*this->player, *enemy) < this->player->getWeapon()->getRange() + 30.f)
				{
					sf::Vector2i enemyPosGrid =
						sf::Vector2i(
							static_cast<int>(enemy->getPosition().x) / static_cast<int>(this->gridSize),
							static_cast<int>(enemy->getPosition().y) / static_cast<int>(this->gridSize)
						);
					sf::IntRect textureRect = sf::IntRect(576, 256, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
					this->tileMap->addTile(enemyPosGrid.x, enemyPosGrid.y, 0, textureRect, 0, 5);
					enemy->getAttributeComponent()->setRewardStatus(false);
				}

				this->enemySystem->removeEnemy(index);
				goto jump;
				
			}
				++index;

		}

		this->player->setEXP();
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
		&& this->player->getWeapon()->getAttackTimer())
	{
		this->player->setInitAttack(true);
	
	}
	
	this->player->setOnEnemyColor(false);

	for (auto *enemy : this->activeEnemies)
	{
		enemy->gainHP();
		//std::cout << enemy->getAttributeComponent()->getRewardStatus();
		enemy->update(dt, this->mousePosView, this->view);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

	  this->updateCombat(enemy, dt);

		//DANGEROUS!!!
	  if (enemy->isStop())
	  {
		  enemy->stopVelocity();


		  //For checking REWARD When we hit
		  if (enemy->getAttributeComponent()->getRewardStatus())
		  {
			  sf::Vector2i enemyPosGrid =
				  sf::Vector2i(
					  static_cast<int>(enemy->getPosition().x) / static_cast<int>(this->gridSize),
					  static_cast<int>(enemy->getPosition().y) / static_cast<int>(this->gridSize)
				  );
			  sf::IntRect textureRect = sf::IntRect(576, 256, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
			  this->tileMap->addTile(enemyPosGrid.x, enemyPosGrid.y, 0, textureRect, 0, 5);
			  enemy->getAttributeComponent()->setRewardStatus(false);
		  }

		  //for removing tile [OnEnemyTile]
		  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			  enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		  {
			  sf::Vector2i dotPosGrid =
				  sf::Vector2i(
					  static_cast<int>(this->player->getTileDOtBound().left) / static_cast<int>(this->gridSize),
					  static_cast<int>(this->player->getTileDOtBound().top + 0) / static_cast<int>(this->gridSize)
				  );
			  this->tileMap->removeTile(dotPosGrid.x, dotPosGrid.y, 0, 4);


		  }
		  //Setting color of Player When it is on Enemy
		  if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		  {

			  this->player->setOnEnemyColor(true);
		  }
		  else
			  this->player->setOnEnemyColor(false);
	  }
		
	 
	}

	this->player->setInitAttack(false);
	

}

void GameState::updateCombat(Enemy* enemy,  const float & dt)
{
	

	if (this->player->getInitAttack()
		&& enemy->getGlobalBounds().intersects(this->player->getWepHitBound())
		&& enemy->getSpriteDistance(*this->player, *enemy) < this->player->getWeapon()->getRange()
		&& enemy->getDamageTimerDone())
	{
		
		if (!enemy->isStop())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXPERIENCE_TAG, this->player->getPosition().x - 40.f, this->player->getPosition().y - 30.f, static_cast<int>(enemy->getGainExp()), "+", "EXP");
		}
		//Get to this!!!!
		//int dmg = static_cast<int>(this->player->getDamage());
		enemy->loseHP(10);
	
		enemy->resetDamageTimer();
		this->tts->addTextTag(DEFAULT_TAG, enemy->getPosition().x, enemy->getPosition().y, static_cast<int>(enemy->getGainExp()), "", "");
	}
	
	

	//Check for enemy damage
	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
		
		if (!enemy->isStop())
		{
			int dmg = enemy->getAttributeComp()->damageMax;
			this->player->loseHP(6);
			this->tts->addTextTag(NEGATIVE_TAG, player->getPosition().x - 30.f, player->getPosition().y, dmg, "-", "HP");
			
		}
	}
}

void GameState::updateDebugText(const float& dt)
{
	std::stringstream ss;

	ss << "Enemies: " << this->activeEnemies.size() << "\n"
		<< "Rewards: " << this->tileMap->getMaxReward() - this->tileMap->getRewardLeft()
		<< "/" << this->tileMap->getMaxReward() << "\n";

	this->debugText.setString(ss.str());
}

void GameState::update(const float& dt)
{
	

	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateToggle();


	this->updateView(dt);

	bool vs = false;


	this->updateDebugText(dt);
	if (!this->checkHome)
	{

		if (!this->paused) //Unpaused update
		{
			if (this->player->getAttributeComponent()->getHP() == 0)
			{
				vs = true;
				
				if (!(sound[3].getStatus() == sf::Sound::Status::Playing) && this->playerDieSound)
				{
					this->buffer[3].loadFromFile("Resources/Audios/die.wav");
					this->sound[3].setBuffer(this->buffer[3]);
					
						this->sound[3].play();
						this->playerDieSound = false;
					
				}
				this->player->getAnimationComponent()->play("DIE_FRONT", dt);
				if (this->player->getAnimationComponent()->isDone("DIE_FRONT"))
				{
						this->gameOver = true;
				}

			}
			if (!this->selectPause && !this->gameOver)
			{

				if (!vs)
					this->updatePlayerInput(dt);

					this->updateTileMap(dt);

					this->updatePlayer(dt);

					this->updatePlayerGUI(dt);

					//Update all enemies
					//CHANGE: Loop outside, and make functions take one enemy at a time

					this->updateCombatAndEnemies(dt);

					//Update systems
					this->tts->update(dt);

					


					this->nextStage();

					


			}
			else
			{

				this->gmenu->update(this->mousePosWindow);
				this->updateGameOverMenuButtons();
			}
		}
		else //Paused update
		{
			if (!this->gameOver)
			{
				/*this->music.stop();*/
				this->pmenu->update(this->mousePosWindow);
				this->updatePauseMenuButtons();
			}
		}
	}
	else
	{

		
		this->updateLevelCompletedMenuButtons();
	}
	
}



void GameState::nextStage()
{
	bool vs = true;
	if (this->countReward != this->tileMap->getRewardLeft())
	{
		this->buffer[0].loadFromFile("Resources/Audios/reward.wav");
		this->sound[0].setBuffer(this->buffer[0]);
		this->sound[0].setVolume(100);
		this->sound[0].play();
		this->countReward = this->tileMap->getRewardLeft();
		vs = true;
	}
	else
		vs = false;
	
	
	if (this->countReward == 0 && vs)
	{
		this->buffer[1].loadFromFile("Resources/Audios/allReward.wav");
		this->sound[1].setBuffer(this->buffer[1]);
		this->sound[1].play();
		this->tileMap->removeTile(this->tileMap->getHomeGridPos().x, this->tileMap->getHomeGridPos().y, 0, 0);
		vs = false;
	}
	this->checkHome = this->tileMap->gethome();
	if (this->checkHome)
	{
		this->buffer[2].loadFromFile("Resources/Audios/win.wav");
		this->sound[2].setBuffer(this->buffer[2]);
		this->sound[2].play();
	}
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition, 
		&this->core_shader,
		this->player->getSpriteCenter(),
		false
	);
	
	for (auto *enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getHitboxCenter(), false);
	}

	this->player->render(this->renderTexture, &this->core_shader, this->player->getHitboxCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getHitboxCenter());
	for (auto* enemy : this->activeEnemies)
	{
		enemy->defferedRenderBar(this->renderTexture);
	}
	this->tts->render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (!this->checkHome)
	{
		if (this->paused) //Pause menu render
		{


			this->pmenu->render(this->renderTexture);
			//window->setMouseCursorVisible(true);

			window->setMouseCursor(pcurser);



		}
		else
		{
			//window->setMouseCursor(curser);
			/*if (!this->selectPause)
				window->setMouseCursor(curser);*/
			if (this->gameOver) //Pause menu render
			{
				if (this->gameOverSound)
				{
					this->buffer[4].loadFromFile("Resources/Audios/gameOver.wav");
					this->sound[4].setBuffer(this->buffer[4]);
					this->sound[4].play();
					this->gameOverSound = false;
				}
				//this->renderTexture.setView(this->renderTexture.getDefaultView());
				this->gmenu->render(this->renderTexture);
				//window->setMouseCursorVisible(true);
				//window->setMouseCursor(pcurser);
				window->setMouseCursor(pcurser);
			}
			else
				window->setMouseCursor(curser);

		}
	}
	else
	{
		if (this->countStage == 15)
		{
			this->emenu->render(this->renderTexture);
		}
		else
		{
			this->lmenu->render(this->renderTexture);
		}
		
		window->setMouseCursor(pcurser);
	}
	
	

	//Debug Text
	this->renderTexture.draw(this->debugText);
	
	
	
	
	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

