#include "GameObject.h"
#include <iostream>
#include <SDL.h>
using namespace std;
GameObject::GameObject(int posX, int posY, int sizeW, int sizeH)
{
	this->posX = posX;
	this->posY = posY;
	this->sizeW = sizeW;
	this->sizeH = sizeH;

}

void GameObject::Print(SDL_Renderer* renderer, int r, int g, int b, int alpha)
{
	SDL_Rect rectGameObject = {posX, posY, sizeW, sizeH};
	SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
	SDL_RenderFillRect(renderer, &rectGameObject);
	
}

void GameObject::PrintText(SDL_Renderer* renderer, SDL_Texture* textTexture)
{
	SDL_Rect rectGameObjectText = { posX+ sizeW / 4, posY+ sizeH / 4, sizeW/2, sizeH/2 };
	SDL_RenderCopy(renderer, textTexture, NULL, &rectGameObjectText);

}