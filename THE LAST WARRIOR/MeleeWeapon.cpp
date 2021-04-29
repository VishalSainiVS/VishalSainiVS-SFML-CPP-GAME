#include "stdafx.h"

#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon( unsigned range,
	std::string texture_file)
	: Weapon(range, texture_file)
{
	this->type = ItemTypes::IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{

}

void MeleeWeapon::generate(const unsigned levelMin, const unsigned levelMax)
{
	

	this->range =  rand() % 10 + this->range;

	
}
 