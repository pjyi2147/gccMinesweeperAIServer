#pragma once

class Tile
{
private:
	// universal
	bool _mine = false;				// is it mine?
	bool _revealed = false;			// is it revealed?
	bool _flagged = false;

	int _neighborCount = 0;				// how many mines does the neighbors have?
	int _col;
	int _row;
	
public:
	// universal
	Tile();
	Tile(int col, int row);

	void printTile();
	
	bool isMine();
	bool isRevealed();
	bool isFlagged();

	int returnRow();
	int returnCol();
	int returnNeighborCount();

	void setMine();
	void setFlag();
	void setNeighborCount(int count);
	void setReveal();

	// for Server
	std::string returnTile();
};