#pragma once
#include <SDL.h>
class GameObject
{
public:
	int posX;
	int posY;
	int sizeW;
	int sizeH;
	int r;
	int g;
	int b;
	int alpha;
	SDL_Renderer* renderer;
	GameObject(int posX,int posY, int sizeW, int sizeH, int r, int g, int b, int alpha, SDL_Renderer* renderer);
	void PrintSDL();
	void ChangeColor(int r, int g, int b, int alpha );
	void PrintText( SDL_Texture* textTexture);

};