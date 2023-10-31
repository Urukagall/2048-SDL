#pragma once
#include <vector>
#include <string>
#include "Box.h"

using namespace std;
class Grid
{
public:

	int size;
	vector<vector<Box>> grid;
	vector<vector<int>> color;
	vector<int> numberValue;
	SDL_Renderer* renderer;

	Grid(std::string sStr, int size);
	Grid(int size, SDL_Renderer* renderer,int screenHeight,int screenWidth);
	~Grid();
	void Print();
	void PlaceNumber();
	int GenerateRandomNumber(int randomNumber);
	bool MoveHorizontal(string move);
	bool MoveVertical(string move);
	void Defeat(bool& ifDefeat);
	void Win(bool& win, int value);
	bool CompareTest(string sStr);


};