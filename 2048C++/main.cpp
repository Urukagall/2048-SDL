#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <windows.h>
#include <time.h>

#include "Box.h"
#include "Grid.h"
#include "Test.h"
#include "GameObject.h"

#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>


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
		std::cerr << "�chec de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		return 1;
	}

	// Initialisation de SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "�chec de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;
		return 1;
	}


	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
		// Gestion de l'erreur
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		// Gestion de l'erreur
	}
	// Obtenir la r�solution de l'�cran
	int screenWidth, screenHeight;
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
		screenWidth = displayMode.w;
		screenHeight = displayMode.h;
	}
	else {
		// Gestion de l'erreur d'obtention de la r�solution de l'�cran
		std::cerr << "�chec de l'obtention de la r�solution de l'�cran : " << SDL_GetError() << std::endl;
		return 1;
	}

	//Chargement de la musique
	Mix_Music* musicHome = Mix_LoadMUS("Music/Home.mp3");
	Mix_Music* musicPlay = Mix_LoadMUS("Music/Play.mp3");
	Mix_Music* musicLose = Mix_LoadMUS("Music/Lose.mp3");
	Mix_Music* musicWin = Mix_LoadMUS("Music/Win.mp3");

	Mix_Chunk* soundEffect = Mix_LoadWAV("Music/Move.mp3");
	// Chargement de la police
	TTF_Font* font = TTF_OpenFont("Font/cyberpunk.ttf", 128); // Remplacez par le chemin de votre police

	if (!font) {
		std::cerr << "�chec du chargement de la police : " << TTF_GetError() << std::endl;
		return 1;
	}

	// Chargement des fonds
	SDL_Surface* homeSurface = IMG_Load("Image/Home.png");
	SDL_Surface* playSurface = IMG_Load("Image/Play.png");
	SDL_Surface* loseSurface = IMG_Load("Image/Lose.png");
	SDL_Surface* winSurface = IMG_Load("Image/Win.png");


	// Chargement des images
	SDL_Surface* lucySurface = IMG_Load("Image/Lucy.png");


	SDL_Window* window = SDL_CreateWindow("Cyberpunk2077-2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Erreur lors de la cr�ation de la fen�tre : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Erreur lors de la cr�ation du renderer : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	// Cr�ation d'une texture � partir de l'image
	SDL_Texture* homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
	SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
	SDL_Texture* loseTexture = SDL_CreateTextureFromSurface(renderer, loseSurface);
	SDL_Texture* winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
	SDL_Texture* lucyTexture = SDL_CreateTextureFromSurface(renderer, lucySurface);
	// Lib�ration de la surface car nous n'en avons plus besoin
	SDL_FreeSurface(homeSurface);
	SDL_FreeSurface(playSurface);
	SDL_FreeSurface(loseSurface);
	SDL_FreeSurface(winSurface);
	SDL_FreeSurface(lucySurface);

	// Cr�ation d'une surface de texte
	SDL_Surface* textHomeSurface1 = TTF_RenderText_Solid(font, "LEVEL     4X4 ", { 238, 229, 0 });
	SDL_Surface* textHomeSurface2 = TTF_RenderText_Solid(font, "LEVEL     8X8 ", { 238, 229, 0 });
	SDL_Surface* textHomeSurface3 = TTF_RenderText_Solid(font, "Quitter", { 238, 229, 0 });
	SDL_Surface* textTitleSurface = TTF_RenderText_Solid(font, "Cyberpunk 2048", { 238, 229, 0 });
	// Cr�ation d'une texture � partir de la surface de texte
	SDL_Texture* textHomeTexture1 = SDL_CreateTextureFromSurface(renderer, textHomeSurface1);
	SDL_Texture* textHomeTexture2= SDL_CreateTextureFromSurface(renderer, textHomeSurface2);
	SDL_Texture* textHomeTexture3 = SDL_CreateTextureFromSurface(renderer, textHomeSurface3);
	SDL_Texture* textTitleTexture = SDL_CreateTextureFromSurface(renderer, textTitleSurface);
	// Lib�ration de la surface, plus n�cessaire
	SDL_FreeSurface(textHomeSurface1);
	SDL_FreeSurface(textHomeSurface2);
	SDL_FreeSurface(textHomeSurface3);
	SDL_FreeSurface(textTitleSurface);

	//// Dessiner un cube rouge
	 

	GameObject title((screenWidth / 20) *4, (screenHeight / 10) , screenWidth , screenHeight / 5, 6, 36, 47, 0, renderer);
	GameObject choice1((screenWidth / 10) * 6, (screenHeight / 10) *4, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);
	GameObject choice2( (screenWidth / 10) * 6, (screenHeight / 10) * 6, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);
	GameObject choice3( (screenWidth / 10) * 6, (screenHeight / 10) * 8, screenWidth / 4, screenHeight / 10, 6, 36, 47,0, renderer);

	GameObject lucy(0, screenHeight / 2, screenWidth/5, screenHeight/2, 6, 36, 47, 0, renderer);
	GameObject lucyText(screenWidth / 6, screenHeight / 2, screenWidth , screenHeight / 10, 6, 36, 47, 0, renderer);

	bool quit = false;
	SDL_Event event;
	int choice = 0;
	int size = 0;
	bool badKey = true;
	string page = "home";
	string choiceMenu[3] = { "Level1","Level2","Quit" };
	Grid* grid = new Grid(size, renderer, screenHeight, screenWidth);

	bool ArrowKeyWasPressed[4] = { false, false, false,false };
	bool defeat = false;
	bool win = false;

	//animation
	int screenRefreshRate = 0; // Fr�quence de rafra�chissement de l'�cran
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
		screenRefreshRate = displayMode.refresh_rate;
	}
	else {
		// Gestion de l'erreur, la fr�quence d'images de l'�cran est inconnue
		screenRefreshRate = 60; // Valeur par d�faut (60 Hz)
	}
	string textToDisplay = "Ceci est un exemple de texte lettre par lettre.";
	int runText = 1;
	int textLength = textToDisplay.length();
	int currentLetter = 0;
	bool textWritten=false;

	SDL_Color textColor = { 255, 255, 255 };
	Mix_PlayMusic(musicHome, -1);
	Mix_VolumeMusic(15);
	Mix_VolumeChunk(soundEffect, 25);
	SDL_RenderClear(renderer);
	while (!quit) {
		if (page == "home") {
			
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				if (event.type == SDL_KEYDOWN) {

					if (event.key.keysym.sym == SDLK_UP) {

						if (choice > 0) {
							choice -= 1;
						}

					}
					else if (event.key.keysym.sym == SDLK_DOWN) {

						if (choice < 2) {
							choice += 1;
						}

					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						//La touche Entrer
						if (choiceMenu[choice] == "Quit") {
							quit = true;
						}
						else if (choiceMenu[choice] == "Level1") {
							Mix_PlayMusic(musicPlay, -1);
							size = 4;
							page = "play";
							grid = new Grid(size, renderer, screenHeight, screenWidth);
							grid->PlaceNumber();
							grid->PlaceNumber();
						}
						else {
							Mix_PlayMusic(musicPlay, -1);
							size = 8;
							page = "play";
							grid = new Grid(size, renderer, screenHeight, screenWidth);

							grid->PlaceNumber();
							grid->PlaceNumber();
						}
					}
				}
				
			}
			SDL_RenderCopy(renderer, homeTexture, NULL, NULL);
			choice1.PrintSDL();
			choice2.PrintSDL();
			choice3.PrintSDL();
			if (choiceMenu[choice] == "Level1") {
				choice1.ChangeColor(129, 253, 223,0);
				choice2.ChangeColor(43, 0, 1, 0);
				choice3.ChangeColor(43, 0, 1, 0);
			}
			else if (choiceMenu[choice] == "Level2") {
				choice1.ChangeColor(43, 0, 1, 0);
				choice2.ChangeColor(129, 253, 223, 0);
				choice3.ChangeColor(43, 0, 1, 0);
			}
			else {
				choice1.ChangeColor(43, 0, 1, 0);
				choice2.ChangeColor(43, 0, 1, 0);
				choice3.ChangeColor(129, 253, 223, 0);

			}
			choice1.PrintText(textHomeTexture1);
			choice2.PrintText(textHomeTexture2);
			choice3.PrintText(textHomeTexture3);
			title.PrintText(textTitleTexture);
		}
		else if (page == "play") {
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, playTexture, NULL, NULL);
			int index = SDL_GetTicks() % screenRefreshRate/2;
			int indexText = SDL_GetTicks() % screenRefreshRate*10;
			if (textWritten) {
				SDL_Surface* textSurface = TTF_RenderText_Solid(font, textToDisplay.c_str(), textColor);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				lucyText.PrintText(textTexture);
				if (0 < index && index < 200) {

					lucy.posX += 10;
					lucy.PrintImage(lucyTexture);
					runText += 1;
				}
				else {
					lucy.posX -= 10;
					lucy.PrintImage(lucyTexture);
				}
			}
			else {
				if (0 < indexText && indexText < 20) {
					string partialText = textToDisplay.substr(0, runText);
					SDL_Surface* textSurface = TTF_RenderText_Solid(font, partialText.c_str(), textColor);
					SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
					// Afficher le texte
					lucyText.PrintText(textTexture);
					lucy.posX += 10;
					lucy.PrintImage(lucyTexture);
					runText += 1;
				}
				else {
					string partialText = textToDisplay.substr(0, runText);
					SDL_Surface* textSurface = TTF_RenderText_Solid(font, partialText.c_str(), textColor);
					SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
					lucyText.PrintText(textTexture);
					lucy.posX -= 10;
					lucy.PrintImage(lucyTexture);

				}
				if (runText > textLength) {
					textWritten = true;
				}
			}

			lucy.posX = 0;
			

			
			//Grid* grid = new Grid(size, renderer, screenHeight, screenWidth);
			grid->Print();
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				if (event.type == SDL_KEYDOWN) {
					if (!ArrowKeyWasPressed[0] && event.key.keysym.sym == SDLK_UP) {
						ArrowKeyWasPressed[0] = true;
						grid->MoveVertical("up");
						grid->PlaceNumber();
						Mix_PlayChannel(-1, soundEffect, 0);
					}
					else if (!ArrowKeyWasPressed[1] && event.key.keysym.sym == SDLK_DOWN) {
						ArrowKeyWasPressed[1] = true;
						grid->MoveVertical("down");
						grid->PlaceNumber();
						Mix_PlayChannel(-1, soundEffect, 0);

					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						ArrowKeyWasPressed[2] = true;
						grid->MoveHorizontal("left");
						grid->PlaceNumber();
						Mix_PlayChannel(-1, soundEffect, 0);
					}
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						ArrowKeyWasPressed[3] = true;
						grid->MoveHorizontal("right");
						grid->PlaceNumber();
						Mix_PlayChannel(-1, soundEffect, 0);
					}
					else if (event.key.keysym.sym == SDLK_ESCAPE) {
						// La touche �chap a �t� enfonc�e
						page = "home";
						Mix_PlayMusic(musicHome, -1);
					}
					
				}else if (event.type == SDL_KEYUP) {
					// R�initialisez la variable lorsque la touche est rel�ch�e
					if (event.key.keysym.sym == SDLK_UP) {
						ArrowKeyWasPressed[0] = false;
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {
						ArrowKeyWasPressed[1] = false;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						ArrowKeyWasPressed[2] = false;
					}
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						ArrowKeyWasPressed[3] = false;
					}
				}
			}
			grid->Defeat(defeat);
			grid->Win(win);
			if (win) {
				page = "Win";
				Mix_PlayMusic(musicWin, -1);
			}else if (defeat) {
				page = "Lose";
				Mix_PlayMusic(musicLose, -1);
			}
			
		}
		else if (page == "Lose") {
			SDL_RenderCopy(renderer, loseTexture, NULL, NULL);
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					// La touche �chap a �t� enfonc�e
					page = "home";
					Mix_PlayMusic(musicHome, -1);
					defeat = false;
				}
				

			}
		}
		else {
			SDL_RenderCopy(renderer, winTexture, NULL, NULL);
			while (SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) {
					quit = true;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					// La touche �chap a �t� enfonc�e
					page = "home";
					Mix_PlayMusic(musicHome, -1);
					win = false;
				}
			}
		}

		// Mise � jour de l'affichage
		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	Mix_Quit();
	SDL_Quit();

}