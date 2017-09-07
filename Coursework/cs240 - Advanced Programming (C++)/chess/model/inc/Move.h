#ifndef CS240_MOVE_H
#define CS240_MOVE_H

#include "Piece.h"

//! Move contains information on where a piece moved from, where it ended up,
//! and a piece captured along the way.
class Move{
public:
	//! Constructor
	//! @ args the piece moved, the piece taken (NULL if none) and start
	//! and end positions
	Move(Piece* moved, Piece* taken, Position* start, Position* end);

	//! Accessors for private data
	Piece* GetMovedPiece() const;
	Piece* GetTakenPiece() const;
	Position* GetStart() const;
	Position* GetEnd() const;
	//! Section devoted to STL functions
//_________________________________________________________________
	Move();
	Move(const Move& other);
	~Move();
	Move& operator= (const Move& other);
	bool operator== (const Move& other);
	bool operator< (const Move& other);
//_________________________________________________________________
private:
	Piece* movedPiece;
	Piece* takenPiece;
	Position* startPos;
	Position* endPos;
};
#endif
