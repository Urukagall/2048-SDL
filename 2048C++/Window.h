#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <time.h>
#include <chrono>

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

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

class Grid;
class Window
{
public:
	SDL_Window* window;
	Grid* grid;
	SDL_Renderer* renderer;
	SDL_Event event;
	TTF_Font* font;
	map<string, Mix_Music*> musicList;
	map<string, SDL_Surface*> surfaceList;
	map<string, SDL_Texture*> textureList;
	map<string, GameObject> gameObjectList;
	bool arrowKeyWasPressed[4] = { false, false, false, false };
	bool defeat = true;
	bool win = false;
	int choice = 0;
	int valueWin = 2048;
	chrono::high_resolution_clock::time_point startTimer;
	chrono::high_resolution_clock::time_point endTimer;
	string choiceMenu[3] = { "Level1","Level2","Quit" };
	string page = "home";
	int size = 0;
	int screenWidth, screenHeight;
	bool quit = false;
	Window();
	void Home();
	void Play();
	void Lose();
	void Win();
	void Close();
};