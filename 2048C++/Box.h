#pragma once
#include "GameObject.h"
class Box : public GameObject
{
public:

	int value;

	Box();
	Box(int posX, int posY, int sizeW, int sizeH, int r, int g, int b, int alpha, SDL_Renderer* renderer);
	~Box();
};