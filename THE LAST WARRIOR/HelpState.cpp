#include "stdafx.h"
#include "HelpState.h"


void HelpState::initVariables()
{
	/*this->modes = sf::VideoMode::getFullscreenModes();
	this->fullscreen = this->stateData->gfxSettings->fullscreen;
	this->vsync = this->stateData->gfxSettings->verticalSync;
	this->antialiasing = this->stateData->gfxSettings->contextSettings.antialiasingLevel;*/
}

void HelpState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HelpState::initKeybinds()
{
	
}

void HelpState::initGui()
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

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/help_back.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);


	//Buttons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(80.f, vm), gui::p2pY(86.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(200, 200, 200, 170), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}



HelpState::HelpState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

HelpState::~HelpState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	
}

//Accessors



//Functions
void HelpState::updateInput(const float& dt)
{

}

void HelpState::updateGui(const float& dt)
{
	/*Updates all the gui elements in the state and handle their functionlaity.*/
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	
	//Quit the game
	if (this->buttons["BACK"]->isPressed() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		
		this->endState();
	}

	
}

void HelpState::update(const float& dt)
{

	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void HelpState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	
}

void HelpState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	
}