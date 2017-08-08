#include <iostream>
#include <vector>
#include <string>

#include "tile.h"

using namespace std;
/// Constructors
// No variables
Tile::Tile()
{
	this->_col = 0;
	this->_row = 0;
}

// with variables 
Tile::Tile(int col, int row)
{
	this->_col = col;
	this->_row = row;
}

// print the tile status
void Tile::printTile()
{
	std::cout << "|";
	if (this->isRevealed() && this->isMine()) cout << "M";
	else if (this->isRevealed())
		cout << this->returnNeighborCount();
	else if (this->isFlagged()) cout << "F";			// Flag
	else cout << "C";									// Covered 
}

/// is series
// is it mine?
bool Tile::isMine()
{
	return this->_mine;
}

// is it revealed?
bool Tile::isRevealed()
{
	return this->_revealed;
}

// is it Flagged?
bool Tile::isFlagged()
{
	return this->_flagged;
}

/// return series
// return its row
int Tile::returnRow()
{
	return this->_row;
}

// return its column
int Tile::returnCol()
{
	return this->_col;
}

// return neighborCount;
int Tile::returnNeighborCount()
{
	return this->_neighborCount;
}

/// set series
// set Mine
void Tile::setMine()
{
	this->_mine = true;
}

// set Flag
void Tile::setFlag()
{
	if (this->_flagged) this->_flagged = false;
	else this->_flagged = true;
}

// set NeighborCount
void Tile::setNeighborCount(int count)
{
	this->_neighborCount = count;
}

// set reveal
void Tile::setReveal()
{
	this->_revealed = true;
}

/// For Server
// return the status as string
string Tile::returnTileState()
{
	if (this->_revealed && this->_mine) return "M";
	else if (this->_revealed)
		return to_string(this->_neighborCount);
	else if (this->_flagged) return "F";			// Flag
	else return "C";								// Covered
}