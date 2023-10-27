#include "Box.h"

Box::Box(int posX, int posY, int sizeW, int sizeH, int r, int g, int b, int alpha, SDL_Renderer* renderer) : GameObject(posX, posY, sizeW, sizeH, r, g, b, alpha, renderer)
{
	this->value = 0;

}

Box::Box() : GameObject(posX, posY, sizeW, sizeH, r, g, b, alpha, renderer)
{
	this->value = 0;

}

Box::~Box()
{

}