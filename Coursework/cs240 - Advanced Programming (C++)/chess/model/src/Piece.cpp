#include "Piece.h"
#include "Board.h"
#include "Checker.h"

Piece::Piece(const std::string& t, bool isW) : type(t), isWhite(isW){
	validMoves = new std::set<Position*>();
}
Piece::~Piece(){}
std::string Piece::GetType() const{
	return type;
}
bool Piece::IsWhite() const{
	return isWhite;
}

void Piece::AddValidMove(Square* toMove, Square* base, Checker* checks){
	Piece* temp;
	temp = toMove->GetOccupant();
	toMove->ChangeOccupant(base->GetOccupant());
	base->ChangeOccupant(NULL);
	if (!checks->IsInCheck(toMove->GetOccupant()->IsWhite())){
		validMoves->insert(toMove->GetPosition());
	}
	base->ChangeOccupant(toMove->GetOccupant());
	toMove->ChangeOccupant(temp);
}


