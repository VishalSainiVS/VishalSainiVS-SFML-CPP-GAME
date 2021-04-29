#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(std::string entity_type)
{
	this->entityType = entity_type;
	
	//this->level = 17;
	this->exp = 0;
	this->expNext = 100;
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->dead = false;
	
	this->updateLevel();
	this->updateStats(true);
	
}

AttributeComponent::~AttributeComponent()
{
	
}

//Functions
std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss	<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
		<< "Attp: " << this->attributePoints << "\n";

	return ss.str();
}

void AttributeComponent::loseHP(const int hp)
{
	this->countTimeOfMaxHP = 0;
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;

}



void AttributeComponent::setRewardStatus(bool status)
{
	this->gotReward = status;
}

bool AttributeComponent::getRewardStatus()
{
	return this->gotReward;
}

std::string AttributeComponent::getEntityType()
{
	return std::string(this->entityType);
}

const int AttributeComponent::getHP()
{
	return this->hp;
}
const int AttributeComponent::getEXP()
{
	return this->exp;
}
void AttributeComponent::setEXP()
{
	 this->exp = 0;
}



void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}
void AttributeComponent::gainMaxHP()
{
	++this->countTimeOfMaxHP;
	
	if (this->countTimeOfMaxHP == this->maxCountTimeOfMaxHP)
	{
		this->hp = this->hpMax;
		
		
	}
	if (this->countTimeOfMaxHP > this->maxCountTimeOfMaxHP)
	{
		this->countTimeOfMaxHP = this->maxCountTimeOfMaxHP;
	}
}

void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

const bool AttributeComponent::isStop() const
{
	
	return this->hp <= 0;
}
const bool AttributeComponent::isDead() const
{
	
	return this->dead;
}
void AttributeComponent::setDead(bool is_dead) 
{
	this->dead = is_dead;
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax			= this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin		= this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax		= this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence		= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::updateLevel()
{
	if(this->exp >= this->expNext)
	{
		this->exp = this->expNext;
	}
}

void AttributeComponent::update()
{
	//this->updateLevel();
}



