#ifndef CS240_PAWN_H
#define CS240_PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(bool isW);
	std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks);
	void AddValidAttacks(Square* toMove, Square* base, Checker* checks);
	void MoveFirst(){hasntMoved = false;}
	void Reset(){hasntMoved = true;}
	static bool Test (std::ostream& os);
private:
	bool hasntMoved;
};

#endif
