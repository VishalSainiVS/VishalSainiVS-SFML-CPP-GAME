#include "stdafx.h"
#include "WeaponHitbox.h"



WeaponHitbox::WeaponHitbox(unsigned range)
{
	this->range = static_cast<float>(range);

	
	//Visual Weapon
	this->hitbox.setOrigin
	(
		(this->hitbox.getGlobalBounds().width / 2.f),
		this->hitbox.getGlobalBounds().height /2.f + this->range );

	this->hitbox.setSize(sf::Vector2f(5.f, this->range));
	this->hitbox.setFillColor(sf::Color(255,255,255,0));
	

	this->dot.setOrigin
	(
		(this->dot.getGlobalBounds().width / 2.f ),
		this->dot.getGlobalBounds().height/ 2.f + this->range);
	this->dot.setRadius(1.f);
	this->dot.setFillColor(sf::Color(255, 255, 255, 150));
	
	this->tileRemoveDot.setOrigin
	(
		(this->tileRemoveDot.getGlobalBounds().width / 2.f ),
		this->tileRemoveDot.getGlobalBounds().height / 2.f + 55.f);
	this->tileRemoveDot.setRadius(1.f);
	this->tileRemoveDot.setFillColor(sf::Color(255, 255, 255, 250));

	// Circle Arround player

	this->circleAroundPlayer.setRadius(this->range + 30.f);
	this->circleAroundPlayer.setFillColor(sf::Color(255, 0,0, 120));
	this->circleAroundPlayer.setOrigin
	(
		(this->circleAroundPlayer.getGlobalBounds().width / 2.f),
		this->circleAroundPlayer.getGlobalBounds().height / 2.f);



	
}
WeaponHitbox::~WeaponHitbox()
{
}

const sf::FloatRect WeaponHitbox::getHitboxBound() const
{
	
	return sf::FloatRect(this->hitbox.getGlobalBounds());
}
const sf::FloatRect WeaponHitbox::getCircleBound() const
{
	
	return sf::FloatRect(this->circleAroundPlayer.getGlobalBounds());
}
sf::FloatRect WeaponHitbox::getTileDotBound()
{
	return this->tileRemoveDot.getGlobalBounds();
}
void WeaponHitbox::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f sprite_center,  unsigned range)
{

	this->hitbox.setPosition(sprite_center);
	this->dot.setPosition(sprite_center);
	this->tileRemoveDot.setPosition(sprite_center);
	this->circleAroundPlayer.setPosition(sprite_center);

	float dX = mouse_pos_view.x - this->hitbox.getPosition().x;
	float dY = mouse_pos_view.y - this->hitbox.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	
	this->hitbox.setRotation(deg + 90.f);
	this->dot.setRotation(deg + 90.f);
	this->tileRemoveDot.setRotation(deg + 90.f);
	
	if (this->range != static_cast<float>(range))
	{
		
		this->range = static_cast<float>(range);
		std::cout <<" range "<< this->hitbox.getSize().y <<"\n";
		this->hitbox.setSize(sf::Vector2f(1.f, static_cast<float>(this->range)));
	}
	
	this->position = this->tileRemoveDot.getPosition();
}

void WeaponHitbox::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
	{
		target.draw(this->hitbox, shader);
		target.draw(this->dot);
		target.draw(this->tileRemoveDot);
		target.draw(this->circleAroundPlayer);
	}
	else
	{
		target.draw(this->hitbox);
		target.draw(this->dot);
		target.draw(this->tileRemoveDot);
	}
}
