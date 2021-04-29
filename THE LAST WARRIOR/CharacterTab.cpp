#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::initText()
{
	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 100));
	this->infoText.setFillColor(sf::Color(200, 200, 200, 240));
	this->infoText.setPosition(this->back.getPosition().x + 20.f, this->back.getPosition().y + 20.f);

	this->infoText.setString(this->player.toStringCharacterTab());

	this->hideWinText.setFont(this->font);
	this->hideWinText.setCharacterSize(gui::calcCharSize(this->vm, 120));
	this->hideWinText.setFillColor(sf::Color(200, 200, 200, 240));
	this->hideWinText.setPosition(this->back.getPosition().x + 20.f, this->back.getPosition().y + 700.f);

	this->hideWinText.setString("PRESS 'C' TO HIDE THIS TAB");

	
}

CharacterTab::CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player)
	: Tab(vm, font, player, false)
{
	//Background
	this->back.setFillColor(sf::Color(0, 20, 20, 200));
	this->back.setSize(sf::Vector2f(gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)));

	this->initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		//Update the character info
		this->infoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTab::render(sf::RenderTarget & target)
{
	if (!this->hidden)
	{
		target.draw(back);
		target.draw(infoText);
		target.draw(hideWinText);

	}	
}
