#pragma once

#ifndef GAMEENDMENU_H
#define GAMEENDMENU_H

#include"Gui.h"

class Gui;

class GameEndMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Private Functions

public:
	GameEndMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~GameEndMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,
		const float y,
		const float width,
		const float height,
		const unsigned char_size,
		const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif
