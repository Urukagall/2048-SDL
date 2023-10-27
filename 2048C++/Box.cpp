#include "Box.h"

Box::Box() : GameObject(posX, posY, sizeW, sizeH, r, g, b, alpha, renderer)
{
	this->value = 0;

}

Box::~Box()
{

}