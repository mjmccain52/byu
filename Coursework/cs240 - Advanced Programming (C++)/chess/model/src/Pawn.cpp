#include "Pawn.h"
#include "Board.h"
#include "UnitTest.h"
#include "Checker.h"
#include "King.h"
using namespace std;

Pawn::Pawn(bool isW) : Piece("pawn", isW), hasntMoved(true){}

std::set<Position*>* Pawn::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	/* a value to make sure the pawns head in the right direction*/
	int way = 1;
	if (isWhite){
		way = -1;
	}
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;
	/*One square forward*/
	if ((row + way) >= 0 && (row + way) <= 7){
		toMove = board->GetSquare(row + way, col);
		if (!toMove->GetOccupant()){
			AddValidMove(toMove, base, checks);
		}
	}
	/*Two squares for first move*/
	if (hasntMoved){
		toMove = board->GetSquare(row + (way * 2), col);
		if (!toMove->GetOccupant() && !board->GetSquare(row + way, col)->GetOccupant()){
			AddValidMove(toMove, base, checks);
		}
	}
	/*Attack right*/
	if ((row + way) >= 0 && (row + way) <= 7 && (col + 1) <= 7){
		toMove = board->GetSquare(row + way, col + 1);
		AddValidAttacks(toMove, base, checks);

	}
	/*Attack Left*/
	if ((row + way) >= 0 && (row + way) <= 7 && (col - 1) >= 0){
		toMove = board->GetSquare(row + way, col - 1);
		AddValidAttacks(toMove, base, checks);
	}
	return validMoves;
}

void Pawn::AddValidAttacks(Square* toMove, Square* base, Checker* checks){
	if (toMove->GetOccupant()){
		if (toMove->GetOccupant()->IsWhite() != isWhite){
			AddValidMove(toMove, base, checks);
		}
	}
}
bool Pawn::Test(ostream& os){
	bool success = true;
	os << "Testing Pawn..." << endl;
	Piece* p = new Pawn (true);
	TEST(p->IsWhite());
	TEST(p->GetType() == "pawn");
	TEST((dynamic_cast<Pawn*>(p))->hasntMoved);
	Board* board = new Board();
	Checker* checks = new Checker(board);
	checks->UpdatePosition(BLACK, new Position(0,0));
	checks->UpdatePosition(WHITE, new Position(7,7));
	board->GetSquare(0,0)->ChangeOccupant(new King(BLACK));
	board->GetSquare(7,7)->ChangeOccupant(new King(WHITE));
	board->GetSquare(6,0)->ChangeOccupant(p);
	//from starting position
	TEST(p->GetValidMoves(board, board->GetSquare(6,0),checks)->size() == 2);
	Piece* p2 = new Pawn (true);
	(dynamic_cast<Pawn*>(p2))->hasntMoved = false;
	board->GetSquare(0,1)->ChangeOccupant(p2);
	//at edge of board
	TEST(p2->GetValidMoves(board, board->GetSquare(0,1),checks)->size() == 0);
	board->GetSquare(0,1)->ChangeOccupant(NULL);
	board->GetSquare(1,3)->ChangeOccupant(p2);
	//normal movement
	TEST(p2->GetValidMoves(board, board->GetSquare(1,3),checks)->size() == 1);
	board->GetSquare(1,3)->ChangeOccupant(NULL);
	board->GetSquare(1,0)->ChangeOccupant(p2);
	//path blocked
	TEST(p2->GetValidMoves(board, board->GetSquare(1,0),checks)->size() == 0);
	board->GetSquare(1,0)->ChangeOccupant(NULL);
	board->GetSquare(1,1)->ChangeOccupant(p2);
	//able to attack
	TEST(p2->GetValidMoves(board, board->GetSquare(1,1),checks)->size() == 2);
	return success;
}

