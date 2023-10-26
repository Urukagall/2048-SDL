#include <iostream>
#include <vector>
#include <random>

#include <string>
#include <windows.h>
#include "Box.h"
#include "Grid.h"
#include "Test.h"
#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
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

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		// Gestion de l'erreur d'initialisation de SDL_image
		std::cerr << "Échec de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		return 1;
	}

	// Obtenir la résolution de l'écran
	int screenWidth, screenHeight;
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
		screenWidth = displayMode.w;
		screenHeight = displayMode.h;
	}
	else {
		// Gestion de l'erreur d'obtention de la résolution de l'écran
		std::cerr << "Échec de l'obtention de la résolution de l'écran : " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* imageSurface = IMG_Load("Image/Home.png");
	if (!imageSurface) {
		// Gestion de l'erreur de chargement de l'image
		std::cerr << "Échec de chargement de l'image : " << IMG_GetError() << std::endl;
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("Cyberpunk2077-2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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
	// Création d'une texture à partir de l'image
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

	// Libération de la surface car nous n'en avons plus besoin
	SDL_FreeSurface(imageSurface);

	//// Dessiner un cube rouge
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_Rect rect = { 100, 100, 200, 200 };
	//SDL_RenderFillRect(renderer, &rect);
	//SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					// La touche Échap a été enfoncée
					quit = true;
				}
			}
		}
		// Effacement de l'écran
		SDL_RenderClear(renderer);

		// Affichage de l'image
		SDL_RenderCopy(renderer, imageTexture, NULL, NULL);

		// Mise à jour de l'affichage
		SDL_RenderPresent(renderer);
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