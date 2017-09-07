#ifndef CS240_KING_H
#define CS240_KING_H

#include "Piece.h"

class King : public Piece
{
public:
	King(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	static bool Test (std::ostream& os);
};

#endif
