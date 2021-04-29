#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"
#include "State.h"


class Entity;

class Player :
	public Entity
{
private:
	//Variables
	Inventory* inventory;
	
	WeaponHitbox* weaponHitbox;
	
	
	bool initAttack;
	bool attacking;
	Weapon* weapon;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	int level;


	sf::SoundBuffer buffer[3];
	sf::Sound sound[3];

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();
	void initInventory();
	void initWeaponHitbox();

public:
	Player(float x, float y, sf::Texture& texture_sheet, int level);
	virtual ~Player();
	


	void setOnEnemyColor(bool onEnemy);

	//Accessors
	AttributeComponent* getAttributeComponent();
	Weapon* getWeapon() const;

	const std::string toStringCharacterTab() const;
	const bool& getInitAttack() const;

	const bool getDamageTimer();

	const unsigned getDamage() const;

	const int getLevel() const;

	const sf::FloatRect getWepHitBound() const;
	const sf::FloatRect getCircleBound() const;
	const sf::FloatRect getTileDOtBound() const;

	//Modifier
	void setInitAttack(const bool initAttack);

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	const int getEXP() const;
	void setEXP();

	
	void updateAnimation(const float& dt, sf::Vector2f& mouse_pos_view);
	void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
	
};

#endif