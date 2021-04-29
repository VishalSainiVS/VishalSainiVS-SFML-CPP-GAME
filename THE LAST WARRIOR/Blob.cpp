#include "stdafx.h"
#include "Blob.h"


//Initializer functions
void Blob::initVariables()
{

}

void Blob::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 2, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 2, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1, 2, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 2, 2, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 3, 2, 3, 60, 64);
}

void Blob::initAI()
{

}

void Blob::initGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 32.f);
}

//Constructors / Destructors
Blob::Blob(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();
	this->initGUI();

	this->createHitboxComponent(this->sprite, 13.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(170.f, 800.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent( "enemy");

	this->generateAttributes();

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}


Blob::~Blob()
{
	delete this->follow;
}

void Blob::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}

void Blob::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	Enemy::update(dt, mouse_pos_view, view);

	this->movementComponent->update(dt);

	//Update GUI REMOVE THIS!!!!
	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 32.f);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);
}

void Blob::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	

	if (show_hitbox)
		this->hitboxComponent->render(target);
}

void Blob::defferedRenderBar(sf::RenderTarget& target)
{
	target.draw(this->hpBar);
}
