#ifndef CS240_ROOK_H
#define CS240_ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	static bool Test (std::ostream& os);
};

#endif
