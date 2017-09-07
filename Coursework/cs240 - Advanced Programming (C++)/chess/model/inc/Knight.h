#ifndef CS240_KNIGHT_H
#define CS240_KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	static bool Test(std::ostream& os);
};

#endif
