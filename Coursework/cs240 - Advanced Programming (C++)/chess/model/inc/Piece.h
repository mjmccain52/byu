#ifndef CS240_PIECE_H
#define CS240_PIECE_H

#include <string>
#include <set>
#include "Position.h"
#include <iostream>

class Board;
class Square;
class Checker;
//! Piece is the parent class for all the various chess pieces
class Piece{
public:
	Piece(const std::string& t, bool isW);
	virtual ~Piece();
	//! Analyzes the board to determine valid moves for the piece
	virtual std::set<Position*>* GetValidMoves(Board* board, Square* base, Checker* checks) =0;
	//! Accessors to protected data
	std::string GetType() const;
	bool IsWhite() const;
	void AddValidMove(Square* toMove, Square* base, Checker* checks);
protected:

	std::string type; //! type of chess piece (pawn, rook, etc.)
	bool isWhite; //! Don't matta' if you're black or white.  Well, actually it does.
	std::set<Position*>* validMoves;
};
#endif

