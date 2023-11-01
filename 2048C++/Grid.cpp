#include "Grid.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include "SDL.h"
#include "SDL_ttf.h"
using namespace std;

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
	color = { { 0, 255, 159 }, { 0, 232, 188 }, { 0, 205, 230 },{ 0, 174, 255 },{ 0, 134, 255 },{ 72, 84, 255 },{ 136, 48, 255 },{ 197, 48, 255 },{ 192, 21, 202 },{ 230, 21, 202 },{ 255, 255, 64 } };

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
					grid[i][j].ChangeColor(color[k-1][0], color[k-1][1], color[k-1][2], 1);
				}else if (grid[i][j].value == 0)
				{
					grid[i][j].ChangeColor(0, 0, 0, 1);
				}
			}
			grid[i][j].PrintSDL();
			if (grid[i][j].value != 0)
			{
				string strValue = to_string(grid[i][j].value);
				const char* charValue = strValue.c_str();
				SDL_Surface* textValueSurface = TTF_RenderText_Solid(font, charValue, {238, 229, 0});
				SDL_Texture* textHomeTexture1 = SDL_CreateTextureFromSurface(renderer, textValueSurface);
				SDL_FreeSurface(textValueSurface);
				grid[i][j].PrintText(textHomeTexture1);
				SDL_DestroyTexture(textHomeTexture1);
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

//méthode place un nombre dans la grille
void Grid::PlaceNumber() {
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

	int indexZero = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j].value == 0)
			{
				indexZero += 1;
				if (indexZero == randomPos)
				{
					if (GenerateRandomNumber(10) == 10){
						grid[i][j].value = 4;
					}else {
						grid[i][j].value = 2;
					}
				}
			}
		}
	}


}

//méthode de déplacement horizontale
bool Grid::MoveHorizontal(string move) {

	//récupère les valuer de la grille avant le déplacement
	vector<vector<Box>> gridStart = grid;

	for (int i = 0; i < size; i++) {
		vector<int> row;

		//rajoute les valeurs non nul de la ligne dans une variable
		for (int j = 0; j < size; j++) {
			if (grid[i][j].value != 0) {
				row.push_back(grid[i][j].value);
			}
		}
		if (move == "left") {
			//rajoute des 0 a la droite de la ligne pour remplir la ligne (simule un déplacement vers la gauche)
			while (row.size() < size) {
				row.push_back(0);
			}
			//fusionne les nombre qui son côte à côte si ils ont les même valeurs, en commencant par la gauche
			for (int j = 0; j < size - 1; j++) {
				if (row[j] == row[j + 1] && row[j] != 0) {
					row[j] *= 2;
					row[j + 1] = 0;
				}
			}
		}
		else {
			//rajoute des 0 a la gauche de la ligne pour remplir la ligne (simule un déplacement vers la droite)
			while (row.size() < size) {
				row.insert(row.begin(), 0);
			}
			//fusionne les nombre qui son côte à côte si ils ont les même valeurs, en commencant par la droite
			for (int j = size - 1; j > 0; j--) {
				if (row[j] == row[j - 1] && row[j] != 0) {
					row[j] *= 2;
					row[j - 1] = 0;
				}
			}
		}



		//rajoute les valeurs non nul de la ligne dans une variable
		vector<int> newRow;
		for (int j = 0; j < size; j++) {
			if (row[j] != 0) {
				newRow.push_back(row[j]);
			}
		}

		//rajoute des 0 a la droite de la ligne pour remplir la ligne (simule un déplacement vers la gauche)
		if (move == "left") {
			while (newRow.size() < size) {
				newRow.push_back(0);
			}
		}
		//rajoute des 0 a la gauche de la ligne pour remplir la ligne (simule un déplacement vers la droite)
		else {
			while (newRow.size() < size) {
				newRow.insert(newRow.begin(), 0);
			}

		}

		//rajoute les valeurs dans la grille
		for (int j = 0; j < size; j++) {
			grid[i][j].value = newRow[j];
		}
	}

	//récupère les valuer de la grille après le déplacement
	vector<vector<Box>> gridEnd = grid;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//si la grille avant et après le déplacement est la même renvoie true pour dire qu'il ne faut pas regénérer un nombre car il n'y a eu aucun mouvement
			if (gridStart[i][j].value != gridEnd[i][j].value) {
				return true;
			}
		}
	}
	return false;
}

bool Grid::MoveVertical(string move) {

	//récupère les valuer de la grille avant le déplacement

	vector<vector<Box>> gridStart = grid;

	for (int i = 0; i < size; i++) {
		vector<int> column;

		//rajoute les valeurs non nul de la colonne dans une variable
		for (int j = 0; j < size; j++) {
			if (grid[j][i].value != 0) {
				column.push_back(grid[j][i].value);
			}
		}
		if (move == "up") {
			//rajoute des 0 en bas de la colonne pour remplir la colonne (simule un déplacement vers le haut)
			while (column.size() < size) {
				column.push_back(0);
			}
			//fusionne les nombre qui son côte à côte si ils ont les même valeurs, en commencant par le haut
			for (int j = 0; j < size - 1; j++) {
				if (column[j] == column[j + 1] && column[j] != 0) {
					column[j] *= 2;
					column[j + 1] = 0;
				}
			}
		}
		else {
			//rajoute des 0 en haut de la colonne pour remplir la ligne (simule un déplacement vers la bas)
			while (column.size() < size) {
				column.insert(column.begin(), 0);
			}
			//fusionne les nombre qui son côte à côte si ils ont les même valeurs, en commencant par le bas
			for (int j = size - 1; j >= 1; j--) {
				if (column[j] == column[j - 1] && column[j] != 0) {
					column[j] *= 2;
					column[j - 1] = 0;
				}
			}
		}


		//rajoute les valeurs non nul de la colonne dans une variable
		vector<int> newColumn;
		for (int j = 0; j < size; j++) {
			if (column[j] != 0) {
				newColumn.push_back(column[j]);
			}
		}
		//rajoute des 0 en bas de la colonne pour remplir la colonne (simule un déplacement vers le haut)
		if (move == "up") {
			while (newColumn.size() < size) {
				newColumn.push_back(0);
			}
		}
		else {
			//rajoute des 0 en haut de la colonne pour remplir la ligne (simule un déplacement vers la bas)
			while (newColumn.size() < size) {
				newColumn.insert(newColumn.begin(), 0);
			}
		}
		//rajoute les valeurs dans la grille
		for (int j = 0; j < size; j++) {
			grid[j][i].value = newColumn[j];
		}
	}


	vector<vector<Box>> gridEnd = grid;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (gridStart[i][j].value != gridEnd[i][j].value) {
				return true;
			}
		}
	}
	return false;

}


bool Grid::FindNumber(int number) {
	int zero = 0;
	for (int i = 0; i < size; i++) {
		for (int y = 0; y < size; y++) {
			if (grid[i][y].value == number) {
				return true;
			}
		}
	}
	return false;
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
void Grid::Win(bool& win, int value) {
	for (int i = 0; i < size; i++) {
		for (int y = 0; y < size; y++) {
			if (grid[i][y].value == value) {
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