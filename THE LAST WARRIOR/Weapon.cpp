#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 50;
	
	
	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}



Weapon::Weapon( std::string texture_file)
	: Item()
{
	this->initVariables();
	

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::"<< texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::Weapon(unsigned range, std::string texture_file)
{
	this->initVariables();


	this->range = range;

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::" << texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{

}



//Accessors
const unsigned & Weapon::getRange() const
{
	return this->range;
}

const bool Weapon::getAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}

	return false;
}
