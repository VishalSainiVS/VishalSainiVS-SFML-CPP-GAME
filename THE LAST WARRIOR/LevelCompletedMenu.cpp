#include "stdafx.h"
#include "LevelCompletedMenu.h"



LevelCompletedMenu::LevelCompletedMenu(sf::VideoMode& vm, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2pY(9.3f, vm)
		)
	);
	this->container.setFillColor(sf::Color(0, 20, 20, 230));
	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm));
	this->menuText.setString("LEVEL COMPLETED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2pY(4.f, vm)
	);
}

LevelCompletedMenu::~LevelCompletedMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& LevelCompletedMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool LevelCompletedMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void LevelCompletedMenu::addButton(
	const std::string key,
	const float y,
	const float width,
	const float height,
	const unsigned char_size,
	const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_size,
		sf::Color(200, 200, 200, 170), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

}

void LevelCompletedMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void LevelCompletedMenu::render(sf::RenderTarget& target)
{

	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}