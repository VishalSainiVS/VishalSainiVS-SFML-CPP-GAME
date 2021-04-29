#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:

	//Variables
	sf::View* view;
	
	sf::Font* font;

	float* keytime;
	float* keytimeMax;

	std::map<std::string, int>* keybinds;

	sf::Vector2i* mousePosScreen;
	sf::Vector2i* mousePosWindow;
	sf::Vector2f* mousePosView;
	sf::Vector2i* mousePosGrid;

	EditorStateData()
	{
		this->view = nullptr;
		this->font = nullptr;
		this->keytime = nullptr;
		this->keybinds = nullptr;
		this->keytimeMax = nullptr;
		this->mousePosScreen = nullptr;
		this->mousePosWindow = nullptr;
		this->mousePosView = nullptr;
		this->mousePosGrid = nullptr;
	};
};

class EditorMode
{
private:

protected:
	StateData* stateData;
	EditorStateData* editorStateData;
	TileMap* tileMap;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

	//Functions
	const bool getKeytime();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif //!EDITORMODE_H