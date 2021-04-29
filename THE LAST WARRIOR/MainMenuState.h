#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"
#include "MapMenu.h"
#include "HelpState.h"




class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	MapMenu* mmenu;
	
	

	sf::Clock keyTimer;
	float keyTimeMax;


	sf::RectangleShape btnBackground;
	std::map<std::string, gui::Button*> buttons;

	sf::VideoMode vm;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initMapMenu();
	void resetGui();
	

public:
	const bool getKeyTime();
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateMapMenuButtons();
	void updateButtons();
	
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif
