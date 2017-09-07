#include "King.h"
#include "Board.h"
#include "UnitTest.h"
#include "Checker.h"
using namespace std;

King::King(bool isW) : Piece("king", isW){}

std::set<Position*>* King::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;

	//South
	if ((row + 1) <= 7){
		toMove = board->GetSquare(row + 1, col);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//North
	if ((row - 1) >= 0){
		toMove = board->GetSquare(row - 1, col);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//East
	if ((col + 1) <= 7){
		toMove = board->GetSquare(row, col + 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//West
	if ((col - 1) >= 0){
		toMove = board->GetSquare(row, col - 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//Southeast
	if ((row + 1) <= 7 && (col + 1) <= 7){
		toMove = board->GetSquare(row + 1, col + 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//Southwest
	if ((row + 1) <= 7 && (col - 1) >= 0){
		toMove = board->GetSquare(row + 1, col - 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//Northeast
	if ((row - 1) >= 0 && (col + 1) <= 7){
		toMove = board->GetSquare(row - 1, col + 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	//NorthWest
	if ((row - 1) >= 0 && (col - 1) >= 0){
		toMove = board->GetSquare(row - 1, col - 1);
		if (toMove->GetOccupant()){
			if (toMove->GetOccupant()->IsWhite() != isWhite){
				checks->UpdatePosition(isWhite, toMove->GetPosition());
				AddValidMove(toMove, base, checks);
				checks->UpdatePosition(isWhite, base->GetPosition());
			}
		}else{
			checks->UpdatePosition(isWhite, toMove->GetPosition());
			AddValidMove(toMove, base, checks);
			checks->UpdatePosition(isWhite, base->GetPosition());
		}
	}
	return validMoves;
}

bool King::Test(ostream& os){
	bool success = true;
	os << "Testing King..." << endl;
	Piece* p = new King (false);
	TEST(!p->IsWhite());
	TEST(p->GetType() == "king");
	return success;
}

