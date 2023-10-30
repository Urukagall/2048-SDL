#pragma once


class Window

{
public:
	SDL_Renderer* renderer;
	SDL_Event event;
	string page = "home";
	int size = 0;
	int screenWidth, screenHeight;
	bool quit = false;
	Window(SDL_Renderer* renderer);
	void Home(Grid* grid);
	void Play();
	void Lose();
	void Win();
	void Close();
};