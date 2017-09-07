#include "Knight.h"
#include "Board.h"
#include "UnitTest.h"
#include "Checker.h"
#include "King.h"
using namespace std;

Knight::Knight(bool isW) : Piece("knight", isW){}

std::set<Position*>* Knight::GetValidMoves(Board* board, Square* base, Checker* checks){
	delete validMoves;
	validMoves = new std::set<Position*>();
	int row = base->GetPosition()->GetRow();
	int col = base->GetPosition()->GetCol();
	Square* toMove;

	int validRow;
	int validCol;

	/*
	 * Loop does some funky math to get all possible knight moves with less code.
	 */
	for (int s = -2; s <= 2; s++){
		int e;
		if (s == 0){continue;}
		if (s % 2 != 0){ //the aforementioned funky math
			e = 2;
		}else{
			e = 1;
		}
		toMove = NULL;
		validRow = row + s;
		validCol = col - e;
		if (validRow >= 0 && validRow <=7 && validCol >= 0 && validCol <= 7){
			toMove = board->GetSquare(validRow, validCol);
			if (toMove->GetOccupant()){
				if (toMove->GetOccupant()->IsWhite() != isWhite){
					AddValidMove(toMove, base, checks);
				}
			}else{
				AddValidMove(toMove, base, checks);
			}
		}

		toMove = NULL;
		validRow = row + s;
		validCol = col + e;
		if (validRow >= 0 && validRow <=7 && validCol >= 0 && validCol <= 7){
			toMove = board->GetSquare(validRow, validCol);
			if (toMove->GetOccupant()){
				if (toMove->GetOccupant()->IsWhite() != isWhite){
					AddValidMove(toMove, base, checks);
				}
			}else{
				AddValidMove(toMove, base, checks);
			}
		}
	}
	return validMoves;
}

bool Knight::Test(ostream& os){
	bool success = true;
	os << "Testing Knight..." << endl;
	Piece* p = new Knight (false);
	TEST(!p->IsWhite());
	TEST(p->GetType() == "knight");
	Board* board = new Board();
	Checker* checks = new Checker(board);
	checks->UpdatePosition(BLACK, new Position(0,0));
	checks->UpdatePosition(WHITE, new Position(7,7));
	board->GetSquare(0,0)->ChangeOccupant(new King(BLACK));
	board->GetSquare(7,7)->ChangeOccupant(new King(WHITE));

	board->GetSquare(1,2)->ChangeOccupant(p);
	TEST(p->GetValidMoves(board, board->GetSquare(1,2), checks)->size() == 5);
	return success;
}

