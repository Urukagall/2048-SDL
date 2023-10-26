#include <iostream>
#include <vector>
#include <random>

#include <string>
#include <windows.h>
#include "Box.h"
#include "Grid.h"
#include "Test.h"
#include <SDL.h>
using namespace std;


void InputSize(int& size) {
	cout << "Entrez la taille du tableau ";
	cin >> size;
}



int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Cube Rouge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Dessiner un cube rouge
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect = { 100, 100, 200, 200 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	int size = 0;

	//Test* gridTest = new Test();

	bool defeat = false;
	bool win = false;
	InputSize(size);

	Grid* grid = new Grid(size);

	grid->Print();



	int numberZero = 0;
	int randomNumber = 0;
	bool leftArrowKeyPressed = false;
	bool rightArrowKeyPressed = false;
	bool upArrowKeyPressed = false;
	bool downArrowKeyPressed = false;

	grid->PlaceNumber();
	grid->PlaceNumber();
	grid->Print();
	while (!defeat && !win) {
		if (GetKeyState(VK_LEFT) & 0x8000) {
			if (!leftArrowKeyPressed) {
				leftArrowKeyPressed = true;
				grid->MoveHorizontal("left");
				grid->PlaceNumber();
				grid->Print();
			}
		}
		else {
			leftArrowKeyPressed = false;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			if (!rightArrowKeyPressed) {
				rightArrowKeyPressed = true;
				grid->MoveHorizontal("right");
				grid->PlaceNumber();
				grid->Print();
			}
		}
		else {
			rightArrowKeyPressed = false;
		}
		if (GetKeyState(VK_UP) & 0x8000) {
			if (!upArrowKeyPressed) {
				upArrowKeyPressed = true;
				grid->MoveVertical("up");
				grid->PlaceNumber();
				grid->Print();
			}
		}
		else {
			upArrowKeyPressed = false;
		}
		if (GetKeyState(VK_DOWN) & 0x8000) {
			if (!downArrowKeyPressed) {
				downArrowKeyPressed = true;
				grid->MoveVertical("down");
				grid->PlaceNumber();
				grid->Print();
			}
		}
		else {
			downArrowKeyPressed = false;
		}
		grid->Defeat(defeat);
		grid->Win(win);
	}

	if (defeat) {
		cout << "Vous avez perdu !!!!";
	}
	else {
		cout << "Vous avez gagne !!!!";
	}

	delete grid;
}