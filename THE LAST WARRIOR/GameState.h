#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"
#include "TextTagSystem.h"
#include "WeaponHitbox.h"
#include "LevelCompletedMenu.h"
#include "GameEndMenu.h"

class GameState :
	public State
{
private:
	sf::Cursor curser;
	sf::Cursor pcurser;

	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;
	GameOverMenu* gmenu;
	LevelCompletedMenu* lmenu;
	GameEndMenu* emenu;
	
	sf::Shader core_shader;

	sf::Clock keyTimer;
	float keyTimeMax;

	sf::Text debugText;

	Player* player;
	PlayerGUI* playerGUI;
	sf::Texture texture;
	
	std::vector<Enemy*> activeEnemies;
	EnemySystem *enemySystem;

	TileMap* tileMap;

	//Systems
	TextTagSystem* tts;


	//Audio
	sf::Music music;
	sf::SoundBuffer buffer[5];
	sf::Sound sound[5];

	bool selectPause ;
	bool gameOver;
	int countStage;
	int countReward;
	bool checkHome;

	bool playerDieSound;
	bool gameOverSound;
	
	
	//Functions
	void initVariables();
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initGameOverMenu();
	void initLevelCompletedMenu();
	void initShaders();
	void initKeyTime();
	void initDebugText();

	void initPlayers();
	void initPlayerGUI();
	void initEnemySystem();
	void initTileMap();
	void initSystems();
	void initAudio();

public:
	GameState(StateData* state_data,int map_no);
	virtual ~GameState();

	//Accessors
	const bool getKeyTime();
	
	
	//Functions
	
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updateToggle();
	void updatePauseMenuButtons();
	void updateGameOverMenuButtons();
	void updateLevelCompletedMenuButtons();
	void updateTileMap(const float& dt);
	void updatePlayer(const float& dt);
	void updateCombatAndEnemies(const float& dt);
	void updateCombat(Enemy* enemy, const float& dt);
	void updateDebugText(const float& dt);
	void update(const float& dt);

	void nextStage();
	void render(sf::RenderTarget* target = NULL);
};

#endif