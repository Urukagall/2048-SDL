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
#include "Window.h"

#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>


using namespace std;



int main(int argc, char* argv[])
{
	// Initialisation de SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Erreur lors de l'initialisation de SDL : " << SDL_GetError() << std::endl;
		return 1;
	}
	// Initialisation de SDL_image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		// Gestion de l'erreur d'initialisation de SDL_image
		cerr << "Échec de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		return 1;
	}

	// Initialisation de SDL_ttf
	if (TTF_Init() == -1) {
		cerr << "Échec de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;

	}
	if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
		// Gestion de l'erreur
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		// Gestion de l'erreur
	}



	Window window;

}