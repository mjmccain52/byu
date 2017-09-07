
#include "Move.h"

Move::Move(Piece* moved, Piece* taken, Position* start, Position* end) :
	movedPiece(moved), takenPiece(taken), startPos(start), endPos(end){}
Piece* Move::GetMovedPiece() const{
	return movedPiece;
}
Piece* Move::GetTakenPiece() const{
	return takenPiece;
}
Position* Move::GetStart() const{
	return startPos;
}
Position* Move::GetEnd() const{
	return endPos;
}


