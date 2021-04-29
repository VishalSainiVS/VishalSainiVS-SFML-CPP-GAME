#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "WeaponHitbox.h"
class Weapon :
	public Item
{
private:
	

	void initVariables();
	

protected:
	sf::Texture weapon_texture;
	sf::Sprite weapon_sprite;

	unsigned damageMin;
	unsigned damageMax;
	unsigned range;

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

public:
	Weapon( std::string texture_file);
	Weapon( unsigned range, 
		std::string texture_file);
	virtual ~Weapon();

	//Accessors
	
	const unsigned& getRange() const;
	const bool getAttackTimer();

	//Function
	virtual Item* clone() = 0;
	virtual void generate(const unsigned levelMin, const unsigned levelMax) = 0;

	virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif
