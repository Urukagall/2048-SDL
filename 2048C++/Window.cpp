#include "Window.h"
#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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


Window::Window() {
	// Obtenir la résolution de l'écran
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
		screenWidth = displayMode.w;
		screenHeight = displayMode.h;
	}
	else {
		// Gestion de l'erreur d'obtention de la résolution de l'écran
		std::cerr << "Échec de l'obtention de la résolution de l'écran : " << SDL_GetError() << std::endl;
	}


	window = SDL_CreateWindow("Cyberpunk2077-2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}


	//Chargement de la musique
	musicList["musicHome"] = Mix_LoadMUS("Music/Home.mp3");
	musicList["musicPlay"] = Mix_LoadMUS("Music/Play.mp3");
	musicList["musicLose"] = Mix_LoadMUS("Music/Lose.mp3");
	musicList["musicWin"] = Mix_LoadMUS("Music/Win.mp3");


	// Chargement de la police
	font = TTF_OpenFont("Font/cyberpunk.ttf", 512); // Remplacez par le chemin de votre police
	if (!font) {
		std::cerr << "Échec du chargement de la police : " << TTF_GetError() << std::endl;
	}


	// Chargement des fonds
	surfaceList["homeSurface"] = IMG_Load("Image/Home.png");
	surfaceList["playSurface"] = IMG_Load("Image/Play.png");
	surfaceList["loseSurface"] = IMG_Load("Image/Lose.png");
	surfaceList["winSurface"] = IMG_Load("Image/Win.png");
	surfaceList["introLucySurface"] = IMG_Load("Image/IntroLucy.png");
	surfaceList["midLucySurface"] = IMG_Load("Image/MidLucy.png");
	surfaceList["winLucySurface"] = IMG_Load("Image/WinLucy.png");
	surfaceList["loseLucySurface"] = IMG_Load("Image/LoseLucy.png");
	// Création d'une surface de texte
	surfaceList["textHomeSurface1"] = TTF_RenderText_Blended(font, "LEVEL     4X4 ", { 238, 229, 0 });
	surfaceList["textHomeSurface2"] = TTF_RenderText_Blended(font, "LEVEL     8X8 ", { 238, 229, 0 });
	surfaceList["textHomeSurface3"] = TTF_RenderText_Blended(font, "Quitter", { 238, 229, 0 });
	surfaceList["textTitleSurface"] = TTF_RenderText_Blended(font, "Cyberpounk 2048", { 238, 229, 0 });
	surfaceList["textWinSurface"] = TTF_RenderText_Blended(font, "Vous vous etes enfuis avec Lucy !!!", { 238, 229, 0 });
	surfaceList["textLoseSurface"] = TTF_RenderText_Blended(font, "Vous n'avez pas reussi a vous enfuir ", { 238, 229, 0 });
	surfaceList["textLose2Surface"] = TTF_RenderText_Blended(font, "la MAXTAC vous a rattrape !!!", { 238, 229, 0 });
	surfaceList["textScoreSurface"] = TTF_RenderText_Blended(font, "Score: 0", {238, 229, 0});
	// Chargement des images
	surfaceList["lucySurface"] = IMG_Load("Image/Lucy.png");


	// Création d'une texture à partir de l'image
	textureList["homeTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["homeSurface"]);
	textureList["playTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["playSurface"]);
	textureList["loseTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["loseSurface"]);
	textureList["winTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["winSurface"]);
	textureList["lucyTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["lucySurface"]);
	textureList["introLucyTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["introLucySurface"]);
	textureList["midLucyTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["midLucySurface"]);
	textureList["winLucyTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["winLucySurface"]);
	textureList["loseLucyTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["loseLucySurface"]);
	// Création d'une texture à partir de la surface de texte
	textureList["textHomeTexture1"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textHomeSurface1"]);
	textureList["textHomeTexture2"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textHomeSurface2"]);
	textureList["textHomeTexture3"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textHomeSurface3"]);
	textureList["textTitleTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textTitleSurface"]);
	textureList["textWinTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textWinSurface"]);
	textureList["textLoseTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textLoseSurface"]);
	textureList["textLose2Texture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textLose2Surface"]);
	textureList["textScoreTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textScoreSurface"]);
	// Libération de la surface
	for (const auto& pair : surfaceList) {
		SDL_FreeSurface(pair.second);
	}

	
	GameObject title((screenWidth / 20) * 4, (screenHeight / 10), screenWidth, screenHeight / 5, 6, 36, 47, 0, renderer);
	GameObject endTitle(0, screenHeight/10 , screenWidth, screenHeight/4, 6, 36, 47, 0, renderer);
	GameObject end2Title(screenWidth/4, screenHeight / 3, screenWidth/2, screenHeight / 8, 6, 36, 47, 0, renderer);
	GameObject choice1((screenWidth / 10) * 6, (screenHeight / 10) * 4, screenWidth / 4, screenHeight / 10, 6, 36, 47, 0, renderer);
	GameObject choice2((screenWidth / 10) * 6, (screenHeight / 10) * 6, screenWidth / 4, screenHeight / 10, 6, 36, 47, 0, renderer);
	GameObject choice3((screenWidth / 10) * 6, (screenHeight / 10) * 8, screenWidth / 4, screenHeight / 10, 6, 36, 47, 0, renderer);

	GameObject lucy(0, screenHeight / 2, screenWidth / 5, screenHeight / 2, 6, 36, 47, 0, renderer);
	GameObject lucyText(-500, 0, screenWidth, screenHeight , 6, 36, 47, 0, renderer);
	GameObject scoreText(0, 0, screenWidth / 5, screenHeight / 8, 6, 36, 47, 0, renderer);


	gameObjectList["title"] = title;
	gameObjectList["endTitle"] = endTitle;
	gameObjectList["end2Title"] = end2Title;
	gameObjectList["choice1"] = choice1;
	gameObjectList["choice2"] = choice2;
	gameObjectList["choice3"] = choice3;
	gameObjectList["lucy"] = lucy;
	gameObjectList["lucyText"] = lucyText;
	gameObjectList["scoreText"] = scoreText;

	this->renderer = renderer;
	
	bool badKey = true;
	
	

	grid = new Grid(size, renderer, screenHeight, screenWidth);
	SDL_Color textColor = { 255, 255, 255 };

	Mix_VolumeMusic(15);

	SDL_RenderClear(renderer);
	
	Mix_PlayMusic(musicList["musicHome"], -1);
	startTime = SDL_GetTicks();
	while (!quit) {
		startTimerFPS = SDL_GetTicks();

		currentTime = SDL_GetTicks();
		deltaTime = currentTime - startTime;

		if (page == "home") {

			Home();
		}
		else if (page == "play") {

			Play();
		}
		else if (page == "Lose") {
			Lose();
		}
		else {
			Win();
		}
		endTimerFPS = SDL_GetTicks();

		frameCount++;

		deltaTimeFPS = endTimerFPS - secondStartTimerFPS;

		if (deltaTimeFPS >= 1000)
		{
			fps = frameCount / (deltaTimeFPS / 1000);
			cout << "FPS : " << fps << endl;
			frameCount = 0;
			secondStartTimerFPS = endTimerFPS;
		}

		SDL_RenderPresent(renderer);

		SDL_Delay((1000 / targetFps) - (endTimerFPS - startTimerFPS));

	}
	Close();
}


void Window::Home() {
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
					Mix_PlayMusic(musicList["musicPlay"], -1);
					size = 4;
					page = "play";
					grid = new Grid(size, renderer, screenHeight, screenWidth);
					grid->PlaceNumber();
					grid->PlaceNumber();
				}
				else {
					Mix_PlayMusic(musicList["musicPlay"], -1);
					size = 8;
					page = "play";
					grid = new Grid(size, renderer, screenHeight, screenWidth);

					grid->PlaceNumber();
					grid->PlaceNumber();
				}
			}
		}

	}
	SDL_RenderCopy(renderer, textureList["homeTexture"], NULL, NULL);
	gameObjectList["choice1"].PrintSDL();
	gameObjectList["choice2"].PrintSDL();
	gameObjectList["choice3"].PrintSDL();
	if (choiceMenu[choice] == "Level1") {
		gameObjectList["choice1"].ChangeColor(129, 253, 223, 0);
		gameObjectList["choice2"].ChangeColor(43, 0, 1, 0);
		gameObjectList["choice3"].ChangeColor(43, 0, 1, 0);
	}
	else if (choiceMenu[choice] == "Level2") {
		gameObjectList["choice1"].ChangeColor(43, 0, 1, 0);
		gameObjectList["choice2"].ChangeColor(129, 253, 223, 0);
		gameObjectList["choice3"].ChangeColor(43, 0, 1, 0);
	}
	else {
		gameObjectList["choice1"].ChangeColor(43, 0, 1, 0);
		gameObjectList["choice2"].ChangeColor(43, 0, 1, 0);
		gameObjectList["choice3"].ChangeColor(129, 253, 223, 0);

	}
	gameObjectList["choice1"].PrintText(textureList["textHomeTexture1"]);
	gameObjectList["choice2"].PrintText(textureList["textHomeTexture2"]);
	gameObjectList["choice3"].PrintText(textureList["textHomeTexture3"]);
	gameObjectList["title"].PrintText(textureList["textTitleTexture"]);
}




void Window::Play() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textureList["playTexture"], NULL, NULL);
	previousScore = grid -> score;

	grid->Print();
	while (SDL_PollEvent(&event) && !win && !defeat) {
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		if (event.type == SDL_KEYDOWN) {
			if (!arrowKeyWasPressed[0] && event.key.keysym.sym == SDLK_UP) {
				arrowKeyWasPressed[0] = true;
				if (grid->MoveVertical("up")) {
					grid->PlaceNumber();
				}
			}
			else if (!arrowKeyWasPressed[1] && event.key.keysym.sym == SDLK_DOWN) {
				arrowKeyWasPressed[1] = true;
				if (grid->MoveVertical("down")) {
					grid->PlaceNumber();
				}


			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				arrowKeyWasPressed[2] = true;
				if (grid->MoveHorizontal("left")) {
					grid->PlaceNumber();
				}
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				arrowKeyWasPressed[3] = true;
				if (grid->MoveHorizontal("right")) {
					grid->PlaceNumber();
				}

			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {
				// La touche Échap a été enfoncée
				page = "home";
				Mix_PlayMusic(musicList["musicHome"], -1);
				printTextIntro = true;


				previousScore = grid->score;
				scoreText = "Score: " + to_string(grid->score);

				surfaceList["textScoreSurface"] = TTF_RenderText_Blended(font, scoreText.c_str(), { 238, 229, 0 });
				textureList["textScoreTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textScoreSurface"]);
			}

		}
		else if (event.type == SDL_KEYUP) {
			// Réinitialisez la variable lorsque la touche est relâchée
			if (event.key.keysym.sym == SDLK_UP) {
				arrowKeyWasPressed[0] = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				arrowKeyWasPressed[1] = false;
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				arrowKeyWasPressed[2] = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				arrowKeyWasPressed[3] = false;
			}
		}
	}
	grid->Defeat(defeat);
	grid->Win(win, valueWin);


	if (previousScore != grid->score)
	{

		previousScore = grid->score;
		scoreText = "Score: " + to_string(grid->score);

		surfaceList["textScoreSurface"] = TTF_RenderText_Blended(font, scoreText.c_str(), { 238, 229, 0 });
		textureList["textScoreTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textScoreSurface"]);
		SDL_FreeSurface(surfaceList["textScoreSurface"]);
	}

	gameObjectList["scoreText"].PrintText(textureList["textScoreTexture"]);
	gameObjectList["lucy"].PrintImage(textureList["lucyTexture"]);
	
	if (deltaTime > 200 && deltaTime < 400) {
		gameObjectList["lucy"].posX = screenWidth / 500;
	}
	else if (deltaTime > 400) {
		startTime = currentTime;
	}
	else {
		gameObjectList["lucy"].posX =0;

	}


	//Text de Lucy
	if (win) {
		if (indexText < targetFps * 3) {
			gameObjectList["lucyText"].PrintImage(textureList["winLucyTexture"]);
		}
		else {
			indexText = 0;
			page = "Win";
			Mix_PlayMusic(musicList["musicWin"], -1);
			printTextIntro = true;
		}
		indexText += 1;


	}
	else if (defeat) {
		if (indexText < targetFps * 3) {
			gameObjectList["lucyText"].PrintImage(textureList["loseLucyTexture"]);
		}
		else {
			indexText = 0;
			page = "Lose";
			Mix_PlayMusic(musicList["musicLose"], -1);
			printTextIntro = true;
		}
		indexText += 1;
	}
	else {
		if (printTextIntro) {
			if (indexText < targetFps * 3) {
				gameObjectList["lucyText"].PrintImage(textureList["introLucyTexture"]);
			}
			else {
				printTextIntro = false;
				printTextMid = true;
				indexText = 0;
			}
			indexText += 1;
		}
		else if(printTextMid) {
			if (grid->FindNumber(valueWin / 2)) {
				if (indexText < targetFps * 3) {
					gameObjectList["lucyText"].PrintImage(textureList["midLucyTexture"]);
					indexText += 1;
				}
				else {
					printTextMid = false;
					indexText = 0;
				}
				
			}
		}
	}






}



void Window::Lose() {
	SDL_RenderCopy(renderer, textureList["loseTexture"], NULL, NULL);
	gameObjectList["endTitle"].PrintText(textureList["textLoseTexture"]);
	gameObjectList["end2Title"].PrintText(textureList["textLose2Texture"]);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE) {
			// La touche Échap a été enfoncée
			grid->score = 0;
			previousScore = grid->score;
			scoreText = "Score: " + to_string(grid->score);

			surfaceList["textScoreSurface"] = TTF_RenderText_Blended(font, scoreText.c_str(), { 238, 229, 0 });
			textureList["textScoreTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textScoreSurface"]);
			SDL_FreeSurface(surfaceList["textScoreSurface"]);
			page = "home";
			Mix_PlayMusic(musicList["musicHome"], -1);
			defeat = false;
		}


	}
}

void Window::Win() {
	SDL_RenderCopy(renderer, textureList["winTexture"], NULL, NULL);
	gameObjectList["end2Title"].PrintText(textureList["textScoreTexture"]);
	gameObjectList["endTitle"].PrintText(textureList["textWinTexture"]);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE) {
			// La touche Échap a été enfoncée
			grid->score = 0;
			previousScore = grid->score;
			scoreText = "Score: " + to_string(grid->score);

			surfaceList["textScoreSurface"] = TTF_RenderText_Blended(font, scoreText.c_str(), { 238, 229, 0 });
			textureList["textScoreTexture"] = SDL_CreateTextureFromSurface(renderer, surfaceList["textScoreSurface"]);
			SDL_FreeSurface(surfaceList["textScoreSurface"]);
			page = "home";
			Mix_PlayMusic(musicList["musicHome"], -1);
			win = false;
		}
	}

}

void Window::Close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	for (const auto& pair : textureList) {
		SDL_DestroyTexture(pair.second);
	}
	for (const auto& pair : musicList) {
		Mix_FreeMusic(pair.second);
	}
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}