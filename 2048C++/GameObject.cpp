#include "GameObject.h"
#include <iostream>
#include <SDL.h>
using namespace std;
GameObject::GameObject(int posX, int posY, int sizeW, int sizeH, int r, int g, int b, int alpha, SDL_Renderer* renderer)
{
	this->posX = posX;
	this->posY = posY;
	this->sizeW = sizeW;
	this->sizeH = sizeH;
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;
	this->renderer  = renderer;
}



void GameObject::PrintSDL()
{
	SDL_Rect rectGameObject = {posX, posY, sizeW, sizeH};
	SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
	SDL_RenderFillRect(renderer, &rectGameObject);
	
}

void GameObject::ChangeColor(int r, int g, int b, int alpha )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;

}
void GameObject::PrintText(SDL_Texture* textTexture)
{
	SDL_Rect rectGameObjectText = { posX+ sizeW / 4, posY+ sizeH / 4, sizeW/2, sizeH/2 };
	SDL_RenderCopy(renderer, textTexture, NULL, &rectGameObjectText);

}

void GameObject::PrintImage(SDL_Texture* imageTexture)
{
	SDL_Rect rectGameObject = { posX, posY, sizeW, sizeH };
	SDL_RenderCopy(renderer, imageTexture, NULL, &rectGameObject);

}