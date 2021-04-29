#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->fullscreen = this->stateData->gfxSettings->fullscreen;
	this->vsync = this->stateData->gfxSettings->verticalSync;
	this->antialiasing = this->stateData->gfxSettings->contextSettings.antialiasingLevel;
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
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

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);


	//Buttons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(73.f, vm), gui::p2pY(83.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 170), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(59.f, vm), gui::p2pY(83.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 170), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["Fullscreen"] = new gui::Button(
		gui::p2pX(65.f, vm), gui::p2pY(51.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, this->checkOnOffInputs(this->stateData->gfxSettings->fullscreen),
		gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(0, 0, 0, 200),
		sf::Color(0, 100, 0, 255), sf::Color(150, 150, 150, 0), sf::Color(200, 0, 0, 200));

	this->buttons["Vsync"] = new gui::Button(
		gui::p2pX(65.f, vm), gui::p2pY(61.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, this->checkOnOffInputs(this->stateData->gfxSettings->verticalSync),
		gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(0, 0, 0, 200),
		sf::Color(0, 100, 0, 255), sf::Color(150, 150, 150, 0), sf::Color(200, 0, 0, 200));

	this->buttons["Antialiasing"] = new gui::Button(
		gui::p2pX(65.f, vm), gui::p2pY(71.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, this->checkOnOffInputs(this->stateData->gfxSettings->contextSettings.antialiasingLevel),
		gui::calcCharSize(vm),
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(0, 0, 0, 200),
		sf::Color(0, 100, 0, 255), sf::Color(150, 150, 150, 0), sf::Color(200, 0, 0, 200));


	//Modes
	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
		

	}

	//Drop down lists
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(48.f, vm), gui::p2pY(42.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm),
		font, modes_str.data(), 10
	);

	//Text init
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
	);

	
	


}

void SettingsState::resetGui()
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

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
	
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

const std::string SettingsState::checkOnOffInputs(short status) const
{
	if(status)
	{
		return "On";
	}
	else
	{
		return "Off";
	}

}

//Functions
void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
	/*Updates all the gui elements in the state and handle their functionlaity.*/
	//Buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//checking
	

	//Button functionality

	//Fullscreen On/Off
	if (this->buttons["Fullscreen"]->isPressed() )
	{
		
		std::cout << this->stateData->gfxSettings->fullscreen << "\n";
		if (this->stateData->gfxSettings->fullscreen)
		{
			this->stateData->gfxSettings->fullscreen = 0;
			
		}
		else
		{
			this->stateData->gfxSettings->fullscreen = 1;
			
		}
	}
	if (this->buttons["Vsync"]->isPressed() )
	{
		std::cout << this->stateData->gfxSettings->verticalSync << "\n";
		if (this->stateData->gfxSettings->verticalSync)
		{
			this->stateData->gfxSettings->verticalSync = 0;
			
		}
		else
		{
			this->stateData->gfxSettings->verticalSync = 1;
			
		}
	}
	if (this->buttons["Antialiasing"]->isPressed() )
	{
		
		if (this->stateData->gfxSettings->contextSettings.antialiasingLevel)
		{
			this->stateData->gfxSettings->contextSettings.antialiasingLevel = 0;
			
		}
		else
		{
			this->stateData->gfxSettings->contextSettings.antialiasingLevel = 1;
			
		}
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		this->fullscreen = this->stateData->gfxSettings->fullscreen;
		this->vsync = this->stateData->gfxSettings->verticalSync;
		this->antialiasing = this->stateData->gfxSettings->contextSettings.antialiasingLevel;
		
		//TEST REMOVE LATER
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		
		this->stateData->gfxSettings->saveToFile("Config/graphics.ini");

		if (this->stateData->gfxSettings->fullscreen)
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Fullscreen);
		else
		{
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
			std::cout <<" else";
		}
		

		this->resetGui();
	
	}
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		if (this->fullscreen != this->stateData->gfxSettings->fullscreen)
		{
			this->stateData->gfxSettings->fullscreen = fullscreen;
		}
		if (this->vsync != this->stateData->gfxSettings->verticalSync)
		{
			this->stateData->gfxSettings->verticalSync = vsync;
		}
		if (this->antialiasing != this->stateData->gfxSettings->contextSettings.antialiasingLevel)
		{
			this->stateData->gfxSettings->contextSettings.antialiasingLevel = this->antialiasing;
		}
		this->endState();
	}

	//Dropdown lists
	for (auto &it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	//Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}