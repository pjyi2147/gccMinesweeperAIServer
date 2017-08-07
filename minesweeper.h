#pragma once
#include <iostream>
#include <vector>

#include "tile.h"

using namespace std;

class MineSweeper
{
private:
	// universal
	int _col;
	int _row;
	int _mineNum;
	Tile** _minefield;

	bool _gameEnd = false;
	bool _win = false;

public:
	// universal
	MineSweeper(int col, int row, int mineNum);
	~MineSweeper();

	void createMinefield(int col, int row);
	void printMineField();
	void EndGame(bool win);
	void checkWin();

	void countMine(int col, int row);
	int countFlag(int col, int row);

	void revealTile(int col, int row);
	void revealDoubleClick(int col, int row);

	void setGameEnd(bool finished);
	void setFlag(int col, int row);
	void setWin(bool win);

	bool returnGameEnd();
	int returnCol();
	int returnRow();
	int returnMineNum();
	bool returnWin();

	// Server only
	string returnMineState();
};