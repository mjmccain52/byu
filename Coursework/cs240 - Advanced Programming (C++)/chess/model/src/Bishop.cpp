#include "Bishop.h"
#include "Board.h"
#include "Checker.h"
#include "King.h"
#include "Pawn.h"
#include "UnitTest.h"
using namespace std;

Bishop::Bishop(bool isW) : Piece("bishop", isW){}

std::set<Position*>* Bishop::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;

	//Southeast
	for (int s = 1, e = 1; row + s < 8 && col + e < 8; s++, e++ ){
		toMove = board->GetSquare(row + s, col + e);
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

	//Southwest
	for (int s = 1, w = 1; row + s < 8 && col - w >= 0; s++, w++ ){
		toMove = board->GetSquare(row + s, col - w);
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
	//Northeast
	for (int n = 1, e = 1; row - n >= 0 && col + e < 8; n++, e++ ){
		toMove = board->GetSquare(row - n, col + e);
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
	//NorthWest
	for (int n = 1, w = 1; row - n >= 0 && col - w >= 0; n++, w++ ){
		toMove = board->GetSquare(row - n, col - w);
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

bool Bishop::Test(ostream& os){
	bool success = true;
	os << "Testing Bishop..." << endl;
	Piece* p = new Bishop (false);
	TEST(!p->IsWhite());
	TEST(p->GetType() == "bishop");
	Board* board = new Board();
	Checker* checks = new Checker(board);
	checks->UpdatePosition(BLACK, new Position(0,0));
	checks->UpdatePosition(WHITE, new Position(7,7));
	board->GetSquare(0,0)->ChangeOccupant(new King(BLACK));
	board->GetSquare(7,7)->ChangeOccupant(new King(WHITE));

	//This Here THOROUGHLY tests the bishop's valid moving capabilities
	board->GetSquare(2,2)->ChangeOccupant(p);
	TEST(p->GetValidMoves(board, board->GetSquare(2,2),checks)->size() == 10);
	return success;
}

