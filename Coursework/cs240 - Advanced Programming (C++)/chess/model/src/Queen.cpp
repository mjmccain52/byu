#include "Queen.h"
#include "Board.h"
#include "UnitTest.h"
#include "King.h" //testing
#include "Pawn.h" //testing
#include "Checker.h"
using namespace std;

Queen::Queen(bool isW) : Piece("queen", isW){}

std::set<Position*>* Queen::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;
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

bool Queen::Test(ostream& os){
	bool success = true;
	os << "Testing Queen..." << endl;
	Piece* p = new Queen (false);
	TEST(!p->IsWhite());
	TEST(p->GetType() == "queen");
	Board* board = new Board();
	Checker* checks = new Checker(board);
	checks->UpdatePosition(BLACK, new Position(0,0));
	checks->UpdatePosition(WHITE, new Position(7,7));
	board->GetSquare(0,0)->ChangeOccupant(new King(BLACK));
	board->GetSquare(7,7)->ChangeOccupant(new King(WHITE));

	board->GetSquare(2,2)->ChangeOccupant(new Queen(WHITE));
	//This test is a heuristic cure-all that checks for all the queens moves at once,
	//including a blocked path.
	TEST(p->GetValidMoves(board, board->GetSquare(2,2),checks)->size() == 24);



	return success;
}

