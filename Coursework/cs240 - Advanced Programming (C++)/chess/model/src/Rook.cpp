#include "Rook.h"
#include "Board.h"
#include "UnitTest.h"
#include "King.h"
#include "Checker.h"
using namespace std;

Rook::Rook(bool isW) : Piece("rook", isW){}

std::set<Position*>* Rook::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;
	//South
	for (int s = 1; row + s < 8; s++){
		toMove = board->GetSquare(row + s, col);
		Piece* temp = toMove->GetOccupant();
		if (!temp){
			AddValidMove(toMove, base, checks);
		}else if (temp->IsWhite() != isWhite){
			AddValidMove(toMove, base, checks);
			break;
		}else{
			break;
		}
	}
	//North
	for (int n = 1; row - n >= 0; n++){
		toMove = board->GetSquare(row - n, col);
		Piece* temp = toMove->GetOccupant();
		if (!temp){
			AddValidMove(toMove, base, checks);
		}else if (temp->IsWhite() != isWhite){
			AddValidMove(toMove, base, checks);
			break;
		}else{
			break;
		}
	}
	//West
	for (int w = 1; col - w >= 0; w++){
		toMove = board->GetSquare(row, col - w);
		Piece* temp = toMove->GetOccupant();
		if (!temp){
			AddValidMove(toMove, base, checks);
		}else if (temp->IsWhite() != isWhite){
			AddValidMove(toMove, base, checks);
			break;
		}else{
			break;
		}
	}
	//East
	for (int e = 1; col + e < 8; e++){
		toMove = board->GetSquare(row, col + e);
		Piece* temp = toMove->GetOccupant();
		if (!temp){
			AddValidMove(toMove, base, checks);
		}else if (temp->IsWhite() != isWhite){
			AddValidMove(toMove, base, checks);
			break;
		}else{
			break;
		}
	}



	return validMoves;
}

bool Rook::Test(ostream& os){
	bool success = true;
	os << "Testing Rook..." << endl;
	Piece* p = new Rook (false);
	TEST(!p->IsWhite());
	TEST(p->GetType() == "rook");
	Board* board = new Board();
	Checker* checks = new Checker(board);
	checks->UpdatePosition(BLACK, new Position(0,0));
	checks->UpdatePosition(WHITE, new Position(7,7));
	board->GetSquare(0,0)->ChangeOccupant(new King(BLACK));
	board->GetSquare(7,7)->ChangeOccupant(new King(WHITE));

	board->GetSquare(0,7)->ChangeOccupant(p);
	TEST(p->GetValidMoves(board, board->GetSquare(0,7), checks)->size() == 13);
	return success;
}

