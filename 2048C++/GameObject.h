#pragma once
#include <SDL.h>
class GameObject
{
public:
	int posX;
	int posY;
	int sizeW;
	int sizeH;
	GameObject(int posX,int posY, int sizeW, int sizeH);
	void Print(SDL_Renderer* renderer,int r, int g, int b, int alpha);
	void PrintText(SDL_Renderer* renderer, SDL_Texture* textTexture);
};