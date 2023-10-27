#include "Grid.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;

const string reset("\033[0m");
const string brightRed("\033[0;91m");
const string brightGreen("\033[0;92m");
const string brightYellow("\033[0;93m");
const string BrightBlue("\033[0;94m");
const string brightMagenta("\033[0;95m");
const string brightCyan("\033[0;96m");
const string red("\033[0;31m");
const string green("\033[0;32m");
const string yellow("\033[0;33m");
const string blue("\033[0;34m");
const string magenta("\033[0;35m");

Grid::Grid(string sStr, int size)
{
	this->size = size;
	grid = vector<vector<Box>>(size, vector<Box>(size));
	int number;
	string letter;
	for (size_t i = 0; i < size * size; i++)
	{
		//grid[i / size][i % size] = Box();
		letter = sStr[i];
		number = stoi(letter);
		grid[i / size][i % size].value = number;
	}
}


Grid::Grid(int size, SDL_Renderer* renderer ,int screenHeight, int screenWidth)
{
	this->renderer = renderer;
	int anchorX = screenWidth / 2;
	int anchorY = screenHeight / 10;
	int boxSize = screenHeight / 5;
	boxSize = boxSize * 0.80;
	color = { brightRed,brightGreen,brightYellow,BrightBlue,brightMagenta,brightCyan,red,green,yellow,blue,magenta };

	this->size = size;
	grid = vector<vector<Box>>(size, vector<Box>(size));

	for (int i = 0; i < size * size; i++)
	{
		if (size == 4)
		{
			grid[i / size][i % size] = Box((i % size) * boxSize + anchorX + (boxSize * 0.20) * (i % size), (i / size) * boxSize + anchorY + (boxSize * 0.20) * (i / size), boxSize, boxSize, 0, 0, 0, 0, renderer);
			
		}
		else {
			grid[i / size][i % size] = Box((i % size) * (boxSize / 2) + anchorX + (boxSize * 0.10) * (i % size), (i / size) * (boxSize / 2) + anchorY + (boxSize * 0.10) * (i / size), (boxSize / 2), (boxSize / 2), 0, 0, 0, 0, renderer);
		}
	}
}

Grid::~Grid()
{

}


void Grid::Print() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < color.size(); k++)
			{
				if (grid[i][j].value != 0 and grid[i][j].value == pow(2, k))
				{
					cout << color[k]; // A changer pour les couleurs
				}
			}
			grid[i][j].PrintSDL();
			if (grid[i][j].value != 0)
			{
				string strValue = to_string(grid[i][j].value);
				const char* charValue = strValue.c_str();
				TTF_Font* font = TTF_OpenFont("Font/cyberpunk.ttf", 128);
				SDL_Surface* textValueSurface = TTF_RenderText_Solid(font, charValue, {238, 229, 0});
				SDL_Texture* textHomeTexture1 = SDL_CreateTextureFromSurface(renderer, textValueSurface);
				grid[i][j].PrintText(textHomeTexture1);
			}
		}
	}
}



int Grid::GenerateRandomNumber(int randomNumber) {
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(1, randomNumber);

	return distribution(generator);
}

void Grid::SpawnNumber(int& randomNumber) {
	int numberZero = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j].value == 0)
			{
				numberZero += 1;
				if (numberZero == randomNumber)
				{
					grid[i][j].value = GenerateRandomNumber(2) * 2;
				}
			}
		}
	}
}
int Grid::PlaceNumber() {
	vector<Box> empty;
	int numberZero = 0;
	int randomPos = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j].value == 0)
			{
				numberZero += 1;
				empty.push_back(grid[i][j]);
			}
		}
	}

	randomPos = GenerateRandomNumber(numberZero);

	SpawnNumber(randomPos);

	return numberZero;
}

void Grid::MoveHorizontal(string move) {
	for (int i = 0; i < size; i++) {
		vector<int> row;

		for (int j = 0; j < size; j++) {
			if (grid[i][j].value != 0) {
				row.push_back(grid[i][j].value);
			}
		}
		if (move == "left") {
			while (row.size() < size) {
				row.push_back(0);
			}
			for (int j = 0; j < size - 1; j++) {
				if (row[j] == row[j + 1] && row[j] != 0) { // a changer pour que la valeur soit bonne pour vers la droite
					row[j] *= 2;
					row[j + 1] = 0;
				}
			}
		}
		else {
			while (row.size() < size) {
				row.insert(row.begin(), 0);
			}
			for (int j = size - 1; j > 0; j--) {
				if (row[j] == row[j - 1] && row[j] != 0) { // a changer pour que la valeur soit bonne pour vers la droite
					row[j] *= 2;
					row[j - 1] = 0;
				}
			}
		}



		// Glissement des chiffres vers la gauche
		vector<int> newRow;
		for (int j = 0; j < size; j++) {
			if (row[j] != 0) {
				newRow.push_back(row[j]);
			}
		}

		if (move == "left") {
			while (newRow.size() < size) {
				newRow.push_back(0);
			}
		}
		else {
			while (newRow.size() < size) {
				newRow.insert(newRow.begin(), 0);
			}

		}

		for (int j = 0; j < size; j++) {
			grid[i][j].value = newRow[j];
		}
	}

}

void Grid::MoveVertical(string move) {
	for (int i = 0; i < size; i++) {
		vector<int> column;

		for (int j = 0; j < size; j++) {
			if (grid[j][i].value != 0) {
				column.push_back(grid[j][i].value);
			}
		}
		if (move == "up") {
			while (column.size() < size) {
				column.push_back(0);
			}
			for (int j = 0; j < size - 1; j++) {
				if (column[j] == column[j + 1] && column[j] != 0) { // a changer pour que la valeur soit bonne pour vers la droite
					column[j] *= 2;
					column[j + 1] = 0;
				}
			}
		}
		else {
			while (column.size() < size) {
				column.insert(column.begin(), 0);
			}
			for (int j = size - 1; j >= 1; j--) {
				if (column[j] == column[j - 1] && column[j] != 0) {
					column[j] *= 2;
					column[j - 1] = 0;
				}
			}
		}


		// Glissement des chiffres vers le bas
		vector<int> newColumn;
		for (int j = 0; j < size; j++) {
			if (column[j] != 0) {
				newColumn.push_back(column[j]);
			}
		}
		if (move == "up") {
			while (newColumn.size() < size) {
				newColumn.push_back(0);
			}
		}
		else {
			while (newColumn.size() < size) {
				newColumn.insert(newColumn.begin(), 0);
			}
		}
		for (int j = 0; j < size; j++) {
			grid[j][i].value = newColumn[j];
		}
	}



}


void Grid::Defeat(bool& ifDefeat) {
	int zero = 0;
	for (int i = 0; i < size; i++) {
		for (int y = 0; y < size; y++) {
			if (grid[i][y].value == 0) {
				zero += 1;
			}
		}
	}
	if (zero == 0) {
		ifDefeat = true;
	}
}
void Grid::Win(bool& win) {
	for (int i = 0; i < size; i++) {
		for (int y = 0; y < size; y++) {
			if (grid[i][y].value == 64) {
				win = true;
				break;
			}
		}
	}

}


bool Grid::CompareTest(string sStr) {
	int number;
	string letter;
	for (size_t i = 0; i < size * size; i++)
	{
		letter = sStr[i];
		number = stoi(letter);
		if (grid[i / size][i % size].value != number) {
			return false;
		}
		
	}
	return true;
}