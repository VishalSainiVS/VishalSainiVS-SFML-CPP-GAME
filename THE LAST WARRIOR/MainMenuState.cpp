#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{
	this->keyTimeMax = .3f;
	this->keyTimer.restart();
	vm = this->stateData->gfxSettings->resolution;
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initGui()
{


	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	////Button background
	//this->btnBackground.setSize(
	//	sf::Vector2f(
	//		static_cast<float>(vm.width / 5), 
	//		static_cast<float>(vm.height)
	//	)
	//);

	//this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
	//this->btnBackground.setFillColor(sf::Color(255, 3, 14, 35));

	//Buttons
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(47.f, vm), 
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(56.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(64.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["HELP_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(73.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Help", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(15.6f, vm), gui::p2pY(83.f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}



void MainMenuState::initMapMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	
	 this->mmenu = new MapMenu(this->stateData->gfxSettings->resolution, this->font);

	this->mmenu->addButton("BACK", 3.f, gui::p2pY(85.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "BACK");

	this->mmenu->addButton("MAP15", 5.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-15");
	this->mmenu->addButton("MAP14", 4.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-14");
	this->mmenu->addButton("MAP13", 3.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-13");
	this->mmenu->addButton("MAP12", 2.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-12");
	this->mmenu->addButton("MAP11", 1.f, gui::p2pY(65.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-11");

	this->mmenu->addButton("MAP10", 5.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-10");
	this->mmenu->addButton("MAP9", 4.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-9");
	this->mmenu->addButton("MAP8", 3.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-8");
	this->mmenu->addButton("MAP7", 2.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-7");
	this->mmenu->addButton("MAP6", 1.f, gui::p2pY(45.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-6");


	this->mmenu->addButton("MAP5", 5.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-5");
	this->mmenu->addButton("MAP4", 4.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-4");
	this->mmenu->addButton("MAP3", 3.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-3");
	this->mmenu->addButton("MAP2", 2.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-2");
	this->mmenu->addButton("MAP1", 1.f, gui::p2pY(25.f, vm), gui::p2pX(13.f, vm), gui::p2pY(13.f, vm), gui::calcCharSize(vm), "MAP-1");
}

void MainMenuState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 *
	 * @return void
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();


	//reseting GUI
	this->initGui();

	//reseting mapMenu
	delete this->mmenu;
	initMapMenu();
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initMapMenu();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete mmenu;
}

const bool MainMenuState::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}
void MainMenuState::updateInput(const float & dt)
{
	
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	
	//New game
	if (this->buttons["GAME_STATE"]->isPressed() && this->getKeyTime())
	{
		
		this->nextMenuState("GAME");
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed() && this->getKeyTime())
	{
		
		this->states->push(new SettingsState(this->stateData));
		
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed() && this->getKeyTime())
	{
	
		/*vm = this->stateData->gfxSettings->resolution;
		this->states->push(new EditorState(this->stateData));*/
	}
	if (this->buttons["HELP_STATE"]->isPressed() && this->getKeyTime())
	{
		vm = this->stateData->gfxSettings->resolution;
		this->states->push(new HelpState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		
		this->endState();
	}
}

void MainMenuState::updateMapMenuButtons()
{
	
		
		if (this->mmenu->isButtonPressed("MAP1") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 1));
			
		}
		else if (this->mmenu->isButtonPressed("MAP2") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 2));
		}

		else if (this->mmenu->isButtonPressed("MAP3") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 3));
		}
		
		else if (this->mmenu->isButtonPressed("MAP4") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData,4));
		}
		
		else if (this->mmenu->isButtonPressed("MAP5") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 5));
		}

		else if (this->mmenu->isButtonPressed("MAP6") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData,6));
		}
		
		else if (this->mmenu->isButtonPressed("MAP7") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 7));
		}
		
		else if (this->mmenu->isButtonPressed("MAP8") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 8));
		}
		
		else if (this->mmenu->isButtonPressed("MAP9") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 9));
		}
		
		else if (this->mmenu->isButtonPressed("MAP10") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData,10));
		}
		
		else if (this->mmenu->isButtonPressed("MAP11") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 11));
		}
		
		else if (this->mmenu->isButtonPressed("MAP12") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 12));
		}
		
		else if (this->mmenu->isButtonPressed("MAP13") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 13));
		}
		
		else if (this->mmenu->isButtonPressed("MAP14") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 14));
		}
		
		else if (this->mmenu->isButtonPressed("MAP15") && this->getKeyTime())
		{
			this->nextMenu = false;
			this->states->push(new GameState(this->stateData, 15));
		}
		
		else if (this->mmenu->isButtonPressed("BACK") && this->getKeyTime())
		{
			this->nextMenu = false;
			
		}
	
}

void MainMenuState::update(const float& dt)
{
	
		this->updateMousePositions();
		this->updateInput(dt);
		
		
	if (!this->nextMenu)
	{
		this->updateButtons();
	}
	else
	{
		if (!this->getKeytime())
		{
			this->mmenu->update(this->mousePosWindow);
			this->updateMapMenuButtons();
		}
	}
	if (this->vm != this->stateData->gfxSettings->resolution)
	{
		this->resetGui();
		vm = this->stateData->gfxSettings->resolution;
		//std::cout << "change resolutoin"<< "\n" <<vm.height<<" " <<vm.width << "\n";
	}
	
	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	
		if (!target)
			target = this->window;

		target->draw(this->background);

		target->draw(this->btnBackground);

		this->renderButtons(*target);

	if (this->nextMenu)
	{
		target->setView(this->window->getDefaultView());
		this->mmenu->render(*target);
	}

	//REMOVE LATER!!!
	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}
