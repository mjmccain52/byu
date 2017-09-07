#ifndef CS240_QUEEN_H
#define CS240_QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	static bool Test (std::ostream& os);
};

#endif
