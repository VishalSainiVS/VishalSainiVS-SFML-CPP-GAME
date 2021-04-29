#include "stdafx.h"
#include "MapMenu.h"


MapMenu::MapMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(0, 20, 20, 150));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) ,
			static_cast<float>(vm.height) - gui::p2pY(8.3f, vm)
		)
	);
	this->container.setFillColor(sf::Color(0, 20, 20, 250));
	
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm) + static_cast<unsigned>(gui::p2pY(3.5f, vm)));
	this->menuText.setString("MAPS");
	this->menuText.setPosition(
		(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f) - gui::p2pY(2.f, vm),
		this->container.getPosition().y + gui::p2pY(6.5f, vm)
	);
}

MapMenu::~MapMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& MapMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool MapMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void MapMenu::addButton(
	const std::string key,
	const float x,
	const float y,
	const float width,
	const float height,
	const unsigned char_size,
	const std::string text)
{
	float k =  ((this->container.getSize().x ) *x / 30.f - width /2.f)  ;

	this->buttons[key] = new gui::Button(
		k+ width*x  , y, width, height,
		&this->font, text, char_size,
		sf::Color(200, 200, 200, 150), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 200)
	);
}

void MapMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void MapMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}