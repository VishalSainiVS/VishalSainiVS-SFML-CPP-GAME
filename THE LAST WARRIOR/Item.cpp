#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

Item::Item()
{
	this->initVariables();
	this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{

}
