#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"
#include "MainMenuState.h"

class SettingsState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	GraphicsSettings gfxSettings;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//
	bool fullscreen;
	bool vsync;
	unsigned int antialiasing;
	
	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	const std::string checkOnOffInputs(short status) const;
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif