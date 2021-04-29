#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(55.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save");
	this->pmenu->addButton("LOAD", gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load");
	this->pmenu->addButton("RESTART", gui::p2pY(35.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Restart");
	this->pmenu->addButton("RESUME", gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Resume");
}
void EditorState::initMapMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->mmenu = new MapMenu(this->stateData->gfxSettings->resolution, this->font);

	this->mmenu->addButton("BACK",3.f, gui::p2pY(85.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "BACK");
	
	this->mmenu->addButton("MAP15", 5.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-15");
	this->mmenu->addButton("MAP14", 4.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-14");
	this->mmenu->addButton("MAP13", 3.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-13");
	this->mmenu->addButton("MAP12", 2.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-12");
	this->mmenu->addButton("MAP11", 1.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-11");
	
	this->mmenu->addButton("MAP10",5.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-10");
	this->mmenu->addButton("MAP9", 4.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-9");
	this->mmenu->addButton("MAP8", 3.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-8");
	this->mmenu->addButton("MAP7", 2.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-7");
	this->mmenu->addButton("MAP6", 1.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-6");


	this->mmenu->addButton("MAP5", 5.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-5");
	this->mmenu->addButton("MAP4",4.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-4");
	this->mmenu->addButton("MAP3",3.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-3");
	this->mmenu->addButton("MAP2",2.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-2");
	this->mmenu->addButton("MAP1",1.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-1");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	
	
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initMapMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
	this->initModes();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;
	delete this->mmenu;

	delete this->tileMap;

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

//Functions

void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))) && this->getKeytime())
	{
		
		if (this->activeMode < this->modes.size() - 1)
		{
			
			this->activeMode++;
			
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP![Already UP]" << "\n";
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))) && this->getKeytime())
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN![Already DOWN]" << "\n";
		}
	}
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{
	
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT") && this->getKeytime())
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE") && this->getKeytime())
		this->nextMenuState("SAVE");
		

	if (this->pmenu->isButtonPressed("LOAD") && this->getKeytime())
		this->nextMenuState("LOAD");

	if (this->pmenu->isButtonPressed("RESUME") && this->getKeytime())
		this->unpauseState();

	if (this->pmenu->isButtonPressed("RESTART") && this->getKeytime())
	{
		auto it = this->buttons.begin();
		for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		{
			delete it->second;
		}

		this->buttons.clear();

		delete this->pmenu;

		delete this->tileMap;

		for (size_t i = 0; i < this->modes.size(); i++)
		{
			delete this->modes[i];
		}
		this->modes.clear();

		this->initVariables();
		this->initEditorStateData();
		this->initView();
		this->initFonts();
		this->initKeybinds();
		this->initPauseMenu();
		this->initMapMenu();
		this->initButtons();
		this->initTileMap();
		this->initGui();
		this->initModes();
		this->unpauseState();
	}
}

void EditorState::updateMapMenuButtons()
{
	if (this->mapsSaveLoad == "SAVE")
	{
		if (this->mmenu->isButtonPressed("MAP1") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map1.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP2") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map2.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP3") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map3.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP4") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map4.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP5") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map5.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP6") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map6.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP7") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map7.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP8") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map8.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP9") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map9.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP10") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map10.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP11") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map11.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP12") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map12.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP13") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map13.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP14") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map14.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP15") && this->getKeytime())
		{
			this->tileMap->saveToFile("Map15.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("BACK") && this->getKeytime())
			this->nextMenu = false;
	}
	else if (this->mapsSaveLoad == "LOAD")
	{
		if (this->mmenu->isButtonPressed("MAP1") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map1.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP2") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map2.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP3") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map3.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP4") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map4.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP5") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map5.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP6") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map6.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP7") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map7.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP8") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map8.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP9") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map9.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP10") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map10.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP11") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map11.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP12") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map12.slmp");
			this->nextMenu = false;
		}

		else if (this->mmenu->isButtonPressed("MAP13") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map13.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP14") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map14.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("MAP15") && this->getKeytime())
		{
			this->tileMap->loadFromFile("Map15.slmp");
			this->nextMenu = false;
		}
		else if (this->mmenu->isButtonPressed("BACK") && this->getKeytime())
			this->nextMenu = false;
	}
}

void EditorState::updateModes(const float & dt)
{
	

	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	

	if (!this->paused) //Unpaused
	{	
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);		
	}
	else //Paused
	{	

		if (!this->nextMenu)
		{
			this->pmenu->update(this->mousePosWindow);
			this->updatePauseMenuButtons();
		}
		else
		{
			this->mmenu->update(this->mousePosWindow);
			this->updateMapMenuButtons();
		}
		
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	
}

void EditorState::renderModes(sf::RenderTarget & target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, sf::Vector2f(), true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);

	this->renderModes(*target);

	if (this->paused) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		if (!this->nextMenu)
		{
			
			this->pmenu->render(*target);
		}
		else
		{
			this->mmenu->render(*target);
		}
	}	
}