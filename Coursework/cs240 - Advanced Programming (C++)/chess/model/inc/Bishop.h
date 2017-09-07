#ifndef CS240_BISHOP_H
#define CS240_BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	static bool Test (std::ostream& os);
};
#endif
