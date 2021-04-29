#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode :
	public EditorMode
{
private:
	sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::RectangleShape collisionSelector;
	gui::TextureSelector* textureSelector;
	sf::IntRect textureRect;
	bool collision;
	int type;
	int layer;
	bool tileAddLock;


	int collisionBoxX = 0;
	int collisionBoxY = 0;


	void initVariables();
	void initGui();

public:
	DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultEditorMode();

	std::string getTypeString(int type) const;

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif //!DEFAULTEDITORMODE_H