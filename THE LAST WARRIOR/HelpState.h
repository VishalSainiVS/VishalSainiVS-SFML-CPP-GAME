

#ifndef HELPSTATE_H
#define HELPSTATE_H

#include "State.h"
#include "Gui.h"


class HelpState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	GraphicsSettings gfxSettings;

	std::map<std::string, gui::Button*> buttons;
	


	
	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	

public:
	HelpState(StateData* state_data);
	virtual ~HelpState();

	//Accessors

	//Functions

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif