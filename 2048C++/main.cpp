#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <windows.h>

#include "Box.h"
#include "Grid.h"
#include "Test.h"
#include "GameObject.h"

#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>



using namespace std;



int main(int argc, char* argv[])
{
	// Initialisation de SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
		return 1;
	}
	// Initialisation de SDL_image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		// Gestion de l'erreur d'initialisation de SDL_image
		std::cerr << "Échec de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		return 1;
	}

	// Initialisation de SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "Échec de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;
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


	// Chargement de la police
	TTF_Font* font = TTF_OpenFont("Font/cyberpunk.ttf", 24); // Remplacez par le chemin de votre police

	if (!font) {
		std::cerr << "Échec du chargement de la police : " << TTF_GetError() << std::endl;
		return 1;
	}

	// Chargement des fonds
	SDL_Surface* homeSurface = IMG_Load("Image/Home.png");
	if (!homeSurface) {
		// Gestion de l'erreur de chargement de l'image
		std::cerr << "Échec de chargement de l'image : " << IMG_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* playSurface = IMG_Load("Image/Play.png");
	if (!playSurface) {
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
	SDL_Texture* homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
	SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
	// Libération de la surface car nous n'en avons plus besoin
	SDL_FreeSurface(homeSurface);
	SDL_FreeSurface(playSurface);

	// Création d'une surface de texte
	SDL_Surface* textHomeSurface1 = TTF_RenderText_Solid(font, "LEVEL     4X4 ", { 238, 229, 0 });
	SDL_Surface* textHomeSurface2 = TTF_RenderText_Solid(font, "LEVEL     8X8 ", { 238, 229, 0 });
	SDL_Surface* textHomeSurface3 = TTF_RenderText_Solid(font, "Quitter", { 238, 229, 0 });
	// Création d'une texture à partir de la surface de texte
	SDL_Texture* textHomeTexture1 = SDL_CreateTextureFromSurface(renderer, textHomeSurface1);
	SDL_Texture* textHomeTexture2= SDL_CreateTextureFromSurface(renderer, textHomeSurface2);
	SDL_Texture* textHomeTexture3 = SDL_CreateTextureFromSurface(renderer, textHomeSurface3);
	// Libération de la surface, plus nécessaire
	SDL_FreeSurface(textHomeSurface1);
	SDL_FreeSurface(textHomeSurface2);
	SDL_FreeSurface(textHomeSurface3);

	//// Dessiner un cube rouge
	 

	
	GameObject choice1((screenWidth / 10) * 6, screenHeight / 4, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);
	GameObject choice2( (screenWidth / 10) * 6, (screenHeight / 4) * 2, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);
	GameObject choice3( (screenWidth / 10) * 6, (screenHeight / 4) * 3, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);
	bool quit = false;
	SDL_Event event;
	int choice = 0;
	int size = 0;
	bool badKey = true;
	string page = "home";
	string choiceMenu[3] = { "Level1","Level2","Quit" };
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (page == "home") {
					//Les Flèches
					if (event.key.keysym.sym == SDLK_UP) {

						if (choice > 0) {
							choice -= 1;
						}
						cout << choice << endl << choiceMenu[choice];
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {

						if (choice < 2) {
							choice += 1;
						}
						cout << choice << endl << choiceMenu[choice];
					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						//La touche Entrer
						if (choiceMenu[choice] == "Quit") {
							quit = true;
						}
						else if (choiceMenu[choice] == "Level1") {
							size = 4;
							page = "play";

						}
						else {
							size = 8;
							page = "play";
						}
					}
					else if (event.key.keysym.sym == SDLK_ESCAPE) {
						// La touche Échap a été enfoncée
						quit = true;
					}
				}
				else if (page == "play") {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						// La touche Échap a été enfoncée
						page = "home";
					}


				}
			}
		}
		// Effacement de l'écran
		SDL_RenderClear(renderer);

		// Affichage de l'image
		if (page == "home") {
			SDL_RenderCopy(renderer, homeTexture, NULL, NULL);
			choice1.Print();
			
			choice2.Print();
			choice3.Print();
			if (choiceMenu[choice] == "Level1") {
				choice1.ChangeColor(13, 45, 60,0);
				choice2.ChangeColor(6, 36, 47, 0);
				choice3.ChangeColor(6, 36, 47, 0);
			}
			else if (choiceMenu[choice] == "Level2") {
				choice1.ChangeColor(6, 36, 47, 0);
				choice2.ChangeColor(13, 45, 60, 0);
				choice3.ChangeColor(6, 36, 47, 0);
			}
			else {
				choice1.ChangeColor(6, 36, 47, 0);
				choice2.ChangeColor(6, 36, 47, 0);
				choice3.ChangeColor(13, 45, 60, 0);

			}
			choice1.PrintText(textHomeTexture1);
			choice2.PrintText(textHomeTexture2);
			choice3.PrintText(textHomeTexture3);
		}
		else if (page == "play") {
			SDL_RenderCopy(renderer, playTexture, NULL, NULL);
			Grid* grid = new Grid(size);
			grid->Print();

		}

		// Mise à jour de l'affichage
		SDL_RenderPresent(renderer);


	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	SDL_Quit();



	//Test* gridTest = new Test();

	/*bool defeat = false;
	bool win = false;
	//Grid* grid = new Grid(size);

	//grid->Print();



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

	delete grid;*/

}