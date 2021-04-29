#include "stdafx.h"

#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->weapon = new Sword( 90, "Resources/Images/Sprites/Player/sword_slash.png");

	this->weapon->generate(1, 3);

	this->damageTimerMax = 500;
}
void Player::initWeaponHitbox()
{
	this->weaponHitbox = new WeaponHitbox(this->weapon->getRange());
}
void Player::initComponents()
{

}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 14, 0, 200, 200);
	this->animationComponent->addAnimation("IDLE_BACK", 10.f,  0, 1, 14, 1, 200, 200);
	this->animationComponent->addAnimation("IDLE_LEFT", 10.f,  0, 2, 14, 2, 200, 200);
	this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 3, 14, 3, 200, 200);

	this->animationComponent->addAnimation("WALK_FRONT", 4.f, 0, 4, 14, 4, 200, 200);
	this->animationComponent->addAnimation("WALK_BACK", 3.f,  0, 5, 14, 5, 200, 200);
	this->animationComponent->addAnimation("WALK_LEFT",3.f,   0, 6, 14, 6, 200, 200);
	this->animationComponent->addAnimation("WALK_RIGHT", 4.f, 0, 7, 14, 7, 200, 200);

	this->animationComponent->addAnimation("ATTACK_FRONT", 2.f, 0, 8, 14, 8, 200, 200);
	this->animationComponent->addAnimation("ATTACK_BACK",  2.f, 0, 9, 14, 9, 200, 200);
	this->animationComponent->addAnimation("ATTACK_LEFT",  2.f, 0, 10, 14, 10, 200, 200);
	this->animationComponent->addAnimation("ATTACK_RIGHT", 2.f, 0, 11, 14, 11, 200, 200);

	

	this->animationComponent->addAnimation("DIE_FRONT", 9.f, 0, 16, 14, 16, 200, 200);
	this->animationComponent->addAnimation("DIE_BACK", 5.f,  0, 17, 14, 17, 200,200);
	this->animationComponent->addAnimation("DIE_LEFT", 5.f,  0, 18, 14, 18, 200, 200);
	this->animationComponent->addAnimation("DIE_RIGHT", 5.f, 0, 19, 14, 19, 200, 200);

	this->animationComponent->addAnimation("HURT_FRONT", 5.f, 0, 12, 14, 12, 200, 200);
	this->animationComponent->addAnimation("HURT_BACK", 5.f, 0, 13, 14, 13, 200, 200);
	this->animationComponent->addAnimation("HURT_LEFT", 5.f, 0, 14, 14, 14, 200, 200);
	this->animationComponent->addAnimation("HURT_RIGHT", 5.f, 0, 15, 14, 15, 200, 200);
}

void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, int level)
{
	this->level = level;

	this->initVariables();
	this->createHitboxComponent(this->sprite, 38.f, 56.f, 44.f, 39.f);
	this->createMovementComponent(220.f, 1400.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent( "player");
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimations();

	this->initInventory();
	this->initWeaponHitbox();

	this->sprite.setScale(.6f, .6f);
}

Player::~Player()
{
	delete this->inventory;
	delete this->weapon;
}

void Player::setOnEnemyColor(bool onEnemy)
{
	if(onEnemy)
	this->sprite.setColor(sf::Color(255,76,53,255));
	else
	this->sprite.setColor(sf::Color::White);
}

//Accessors
AttributeComponent * Player::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon * Player::getWeapon() const
{
	return this->weapon;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;
	const AttributeComponent* ac = this->attributeComponent;
	const Weapon* w = this->weapon;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n"
		
		
		<< "Weapon Type: " << "Sword" << "\n"
		;

	return ss.str();
}

const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

const bool Player::getDamageTimer()
{
	if(this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{ 
		this->damageTimer.restart();
		return true;
	}

	return false;
}

const unsigned Player::getDamage() const
{
	return 10;
}

const int Player::getLevel() const
{
	return this->level;
}

const sf::FloatRect Player::getWepHitBound() const
{
	
	return this->weaponHitbox->getHitboxBound();
}
const sf::FloatRect Player::getCircleBound() const
{
	
	return this->weaponHitbox->getCircleBound();
}
const sf::FloatRect Player::getTileDOtBound() const
{
	
	return this->weaponHitbox->getTileDotBound();
}

void Player::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

const int Player::getEXP() const
{
	return this->attributeComponent->getEXP();
}
void Player::setEXP()
{
	this->attributeComponent->setEXP();
}





void Player::updateAnimation(const float & dt, sf::Vector2f& mouse_pos_view)
{
	const AttributeComponent* ac = this->attributeComponent;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
	{
		this->attacking = true;
		this->buffer[0].loadFromFile("Resources/Audios/attack.wav");
		this->sound[0].setBuffer(this->buffer[0]);
		this->sound[0].setVolume(30);
		this->sound[0].setPitch(1.5);
		this->sound[0].play();
		
		
	}
	 if (this->attacking && ac->hp != 0)
	{
		if (((mouse_pos_view.y - this->sprite.getPosition().y) > (mouse_pos_view.x - this->sprite.getPosition().x)) &&
			((mouse_pos_view.y - this->sprite.getPosition().y) > (this->sprite.getPosition().x - mouse_pos_view.x + 80)) &&
			(mouse_pos_view.y > this->sprite.getPosition().y))
		{
			if (this->animationComponent->play("ATTACK_FRONT", dt))
				this->attacking = false;
		}
		else if (((this->sprite.getPosition().y + 80 - mouse_pos_view.y) > (mouse_pos_view.x - this->sprite.getPosition().x)) &&
			((this->sprite.getPosition().y + 80 - mouse_pos_view.y) > (this->sprite.getPosition().x - mouse_pos_view.x + 80)) &&
			this->sprite.getPosition().y + 80 > mouse_pos_view.y)
		{
			if (this->animationComponent->play("ATTACK_BACK", dt))
				this->attacking = false;
		}
		else if (((mouse_pos_view.x - this->sprite.getPosition().x) > (this->sprite.getPosition().y - mouse_pos_view.y + 80)) &&
			((mouse_pos_view.x - this->sprite.getPosition().x) > (mouse_pos_view.y - this->sprite.getPosition().y)) &&
			mouse_pos_view.x > this->sprite.getPosition().x)
		{
			if (this->animationComponent->play("ATTACK_RIGHT", dt))
				this->attacking = false;
		}
		else if (((this->sprite.getPosition().x + 80 - mouse_pos_view.x) > (this->sprite.getPosition().y - mouse_pos_view.y + 80)) &&
			((this->sprite.getPosition().x + 80 - mouse_pos_view.x) > (mouse_pos_view.y - this->sprite.getPosition().y)) &&
			this->sprite.getPosition().x + 80 > mouse_pos_view.x)
		{
			if (this->animationComponent->play("ATTACK_LEFT", dt))
				this->attacking = false;
		}
	}
	else if (this->movementComponent->getState(IDLE) && ac->hp != 0)
	{
		if(((mouse_pos_view.y - this->sprite.getPosition().y ) > (mouse_pos_view.x - this->sprite.getPosition().x )) &&
			((mouse_pos_view.y - this->sprite.getPosition().y) > (this->sprite.getPosition().x - mouse_pos_view.x +80)) &&
			(mouse_pos_view.y > this->sprite.getPosition().y ))
				this->animationComponent->play("IDLE_FRONT", dt);

		else if (((this->sprite.getPosition().y +80 - mouse_pos_view.y) > (mouse_pos_view.x - this->sprite.getPosition().x)) &&
			((this->sprite.getPosition().y +80- mouse_pos_view.y) > (this->sprite.getPosition().x - mouse_pos_view.x +80)) &&
			this->sprite.getPosition().y +80> mouse_pos_view.y )
				this->animationComponent->play("IDLE_BACK", dt);

		else if (((mouse_pos_view.x - this->sprite.getPosition().x) > (this->sprite.getPosition().y - mouse_pos_view.y +80)) &&
			((mouse_pos_view.x - this->sprite.getPosition().x) > (mouse_pos_view.y - this->sprite.getPosition().y)) &&
			mouse_pos_view.x > this->sprite.getPosition().x )
				this->animationComponent->play("IDLE_RIGHT", dt);

		else if (((this->sprite.getPosition().x +80 - mouse_pos_view.x  ) > (this->sprite.getPosition().y - mouse_pos_view.y +80 )) &&
			((this->sprite.getPosition().x +80 - mouse_pos_view.x ) > (mouse_pos_view.y - this->sprite.getPosition().y))&&
			this->sprite.getPosition().x +80 > mouse_pos_view.x )
				this->animationComponent->play("IDLE_LEFT", dt);
		
	}
	else if (this->movementComponent->getState(MOVING_LEFT) && ac->hp != 0)
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_BACK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_FRONT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	
}

void Player::update(const float & dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt, mouse_pos_view);
	
	this->hitboxComponent->update();
	
	this->weaponHitbox->update(mouse_pos_view, this->getSpriteCenter(), this->weapon->getRange() );

	this->weapon->update(mouse_pos_view, sf::Vector2f(this->getSpriteCenter().x, this->getSpriteCenter().y + 5.f));

	if (this->attributeComponent->getEXP() >= 100)
	{
		this->weaponHitbox->circleAroundPlayer.setFillColor(sf::Color(255, 0, 0, 50));
	}
	else
	{
		this->weaponHitbox->circleAroundPlayer.setFillColor(sf::Color(255, 0, 0, 0));
	}

	if (this->movementComponent->getVelocity().x || this->movementComponent->getVelocity().y)
	{
		
		
		if (!(sound[1].getStatus() == sf::Sound::Status::Playing))
		{
			this->buffer[1].loadFromFile("Resources/Audios/walk.wav");
			this->sound[1].setBuffer(this->buffer[1]);
			this->sound[1].setPitch(static_cast<float>(2.2));
			this->sound[1].setVolume(100);
			this->sound[1].setPosition(0, 0, 3.f);
			this->sound[1].play();
		}
		    
		
	}
	
	
}



void Player::render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		this->weaponHitbox->render(target, shader);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		this->weapon->render(target, shader);
		
	}
	else 
	{
		this->weaponHitbox->render(target);
		target.draw(this->sprite);
		this->weapon->render(target);
	
	}
	
	if(show_hitbox)
		this->hitboxComponent->render(target);
}
