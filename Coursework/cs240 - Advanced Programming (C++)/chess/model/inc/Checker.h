#ifndef CS240_CHECKER_H
#define CS240_CHECKER_H

#include "Position.h"
#include "Board.h"

class Checker{
public:
	Checker(Board* b);
	void UpdatePosition(bool isWhite, Position* pos);
	bool IsInCheck(bool isWhite);

	static bool Test(std::ostream& os);
private:
	bool CheckNorthSouth(bool isWhite);
	bool CheckEastWest(bool isWhite);
	bool CheckNwSe(bool isWhite);
	bool CheckNeSw(bool isWhite);
	bool CheckKnight(bool isWhite);
	bool CheckDiagonal(bool isWhite, bool& safe, Piece* target,
			int row, int col, int targetRow, int targetCol);
	Position* whiteKing;
	Position* blackKing;
	Board* board;
};

#endif
