#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
{
	//Text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);

	//General GUI
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	
	this->collisionSelector.setSize(sf::Vector2f(this->tileMap->collisionBoxGB.width,
		this->tileMap->collisionBoxGB.height));
	this->collisionSelector.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionSelector.setOutlineThickness(1.f);
	this->collisionSelector.setOutlineColor(sf::Color::Red);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(
		20.f, 20.f, 960.f, 576.f,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		*this->editorStateData->font, "TS"
	);

	//Buttons
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete this->textureSelector;
}

std::string DefaultEditorMode::getTypeString(int type) const
{
	if (type == 0)
		return "Default";
	if (type == 1)
		return "DOODAD";
	
	if (type == 2)
		return "ENEMYSPAWNER";
	
	if (type == 3)
		return "DAMAGING";
	
	if (type == 4)
		return "ONENEMY";
	if (type == 5)
		return "REWARD";
	if (type == 6)
		return "HOME";

	return "Out of Limit";
}

//Functions
void DefaultEditorMode::updateInput(const float & dt)
{
	//collision box resize 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("INCREASE_COLLISIONBOX_WIDTH"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			if (this->tileMap->collisionBoxGB.width > 1)
				this->tileMap->collisionBoxGB.width--;
		}
		else if (this->tileMap->collisionBoxGB.left <
			(static_cast<float>(this->editorStateData->mousePosGrid->x) * this->tileMap->gridSize) +
			(this->tileMap->gridSize - this->tileMap->collisionBoxGB.width))
			this->tileMap->collisionBoxGB.width++;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("INCREASE_COLLISIONBOX_HIGHT"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			if (this->tileMap->collisionBoxGB.height > 1)
				this->tileMap->collisionBoxGB.height--;

		}
		else if (this->tileMap->collisionBoxGB.top < (static_cast<float>(this->editorStateData->mousePosGrid->y) * this->tileMap->gridSize) + (this->tileMap->gridSize - this->tileMap->collisionBoxGB.height))
			this->tileMap->collisionBoxGB.height++;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("MOVE_COLLISIONBOX_DOWN"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			if (this->tileMap->collisionBoxGB.top > static_cast<float>(this->editorStateData->mousePosGrid->y) * this->tileMap->gridSize)
				this->collisionBoxX--;
		}
		else if (this->tileMap->collisionBoxGB.top < (static_cast<float>(this->editorStateData->mousePosGrid->y) * this->tileMap->gridSize) + (this->tileMap->gridSize - this->tileMap->collisionBoxGB.height))
		{
			this->collisionBoxX++;
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("MOVE_COLLISIONBOX_RIGHT"))) && this->getKeytime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			if (this->tileMap->collisionBoxGB.left > (static_cast<float>(this->editorStateData->mousePosGrid->x) * this->tileMap->gridSize))
				this->collisionBoxY--;
		}
		else if (this->tileMap->collisionBoxGB.left < (static_cast<float>(this->editorStateData->mousePosGrid->x) * this->tileMap->gridSize) + (this->tileMap->gridSize - this->tileMap->collisionBoxGB.width))
		{
			this->collisionBoxY++;
		}

	}

	this->collisionSelector.setSize(sf::Vector2f(this->tileMap->collisionBoxGB.width,
		this->tileMap->collisionBoxGB.height));

	this->tileMap->collisionBoxGB.left = (static_cast<float>(this->editorStateData->mousePosGrid->x) * this->tileMap->gridSize) + collisionBoxY;
	this->tileMap->collisionBoxGB.top = (static_cast<float>(this->editorStateData->mousePosGrid->y) * this->tileMap->gridSize) + this->collisionBoxX;

	this->collisionSelector.setPosition(sf::Vector2f(this->tileMap->collisionBoxGB.left, this->tileMap->collisionBoxGB.top));







	//Add a tile to the tilemap
	if (!this->tileAddLock)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
			{
				if (!this->textureSelector->getActive())
				{
					if (this->tileAddLock)
					{
						if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
						{
							this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
						}
					}
					else
					{
						this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->textureRect = this->textureSelector->getTextureRect();
				}
			}
		}
		//Remove a tile from the tilemap
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
			{
				std::cout << this->type << " vs\n";
				if (!this->textureSelector->getActive())
					this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0,this->type);
			}
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
			{
				if (!this->textureSelector->getActive())
				{
					if (this->tileAddLock)
					{
						if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
						{
							this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
						}
					}
					else
					{
						this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->textureRect = this->textureSelector->getTextureRect();
				}
			}
		}
		//Remove a tile from the tilemap
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) )
		{
			if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
			{
				
				if (!this->textureSelector->getActive())
					this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0,this->type);
			}
		}
	}
	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("INCREASE_TYPE"))) && this->getKeytime())
	{
		//CHANGE TO LIMIT TO MAX TYPE!!!!
		if(type < 6)
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if (this->type > 0)
			--this->type;
	}

	//Set lock on / off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_TILE_LOCK"))) && this->getKeytime())
	{
		if (this->tileAddLock)
			this->tileAddLock = false;
		else
			this->tileAddLock = true;
	}


	
}

void DefaultEditorMode::updateGui(const float & dt)
{
	this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
		//this->collisionSelector.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	}

	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);
	
	std::stringstream ss;
	ss << this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y <<
		"\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->getTypeString(this->type) <<
		"\n" << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) <<
		"\n" << "Tile lock: " << this->tileAddLock;

	this->cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float & dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
	this->tileMap->update();
}

void DefaultEditorMode::renderGui(sf::RenderTarget & target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
		target.draw(this->collisionSelector);
	}

	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
