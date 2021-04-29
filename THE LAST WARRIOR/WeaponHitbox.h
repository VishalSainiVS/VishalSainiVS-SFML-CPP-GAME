#pragma once
#include "Weapon.h"
class WeaponHitbox 
{
public:
	sf::RectangleShape hitbox;
	sf::CircleShape dot;
	sf::CircleShape tileRemoveDot;
	sf::Vector2f position;
	sf::CircleShape circleAroundPlayer;
	float range;
	
	

	WeaponHitbox(unsigned range);
	virtual ~WeaponHitbox();

	sf::FloatRect getTileDotBound();
	const sf::FloatRect getHitboxBound() const;
	const sf::FloatRect getCircleBound() const;
	
	void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f sprite_center, unsigned range);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

