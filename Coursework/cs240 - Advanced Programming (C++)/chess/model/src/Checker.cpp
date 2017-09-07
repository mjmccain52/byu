#include "Checker.h"
#include "UnitTest.h"
#include "Pawn.h"//for testing
#include "Queen.h" // for testing
#include "King.h" // for testing
#include "Knight.h"
using namespace std;

Checker::Checker(Board* b) : board(b){}
void Checker::UpdatePosition(bool isWhite, Position* pos){;
	if (isWhite){
		whiteKing = pos;
	}else{
		blackKing = pos;
	}
}
bool Checker::IsInCheck(bool isWhite){

	if (CheckNorthSouth(isWhite)){return true;}
	if (CheckEastWest(isWhite)){return true;}
	if (CheckNwSe(isWhite)){return true;}
	if (CheckNeSw(isWhite)){return true;}
	if (CheckKnight(isWhite)){return true;}


	return false;
}

bool Checker::CheckNorthSouth(bool isWhite){
	Position* king;
	if (isWhite){
		king = whiteKing;
	}else{
		king = blackKing;
	}
	bool safeNorth = false;
	bool safeSouth = false;
	for (int n = king->GetRow() - 1, s = king->GetRow() + 1; !safeNorth || !safeSouth; n--, s++){
		if (s > 7 || safeSouth){
			safeSouth = true;
		}else{
			Piece* southPiece = board->GetSquare(s, king->GetCol())->GetOccupant();
			string type;
			if (southPiece != NULL){
				type = southPiece->GetType();
				if (southPiece->IsWhite() == isWhite || type == "pawn" || type == "bishop"
					|| type == "knight"|| (type == "king" && s > king->GetRow() + 1)){
					safeSouth = true;
				}else {
					return true;
				}
			}
		}

		if (n < 0 || safeNorth){
					safeNorth = true;
		}else{
			Piece* northPiece = board->GetSquare(n, king->GetCol())->GetOccupant();
			string type;
			if (northPiece != NULL){
				type = northPiece->GetType();
				if (northPiece->IsWhite() == isWhite || type == "pawn" || type == "bishop"
					|| type == "knight" || (type == "king" && n < king->GetRow() - 1)){
					safeNorth = true;
				}else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Checker::CheckEastWest(bool isWhite){
	Position* king;
	if (isWhite){
		king = whiteKing;
	}else{
		king = blackKing;
	}
	bool safeWest = false;
	bool safeEast = false;
	for (int w = king->GetCol() - 1, e = king->GetCol() + 1; !safeWest || !safeEast; w--, e++){
		if (e > 7 || safeEast){
			safeEast = true;
		}else{
			Piece* eastPiece = board->GetSquare(king->GetRow(), e)->GetOccupant();
			string type;
			if (eastPiece != NULL){
				type = eastPiece->GetType();
				if (eastPiece->IsWhite() == isWhite || type == "pawn" || type == "bishop"
					|| type == "knight"|| (type == "king" && e > king->GetCol() + 1)){
					safeEast = true;
				}else {
					return true;
				}
			}
		}

		if (w < 0 || safeWest){
					safeWest = true;
		}else{
			Piece* westPiece = board->GetSquare(king->GetRow(), w)->GetOccupant();
			string type;
			if (westPiece != NULL){
				type = westPiece->GetType();
				if (westPiece->IsWhite() == isWhite || type == "pawn" || type == "bishop"
					|| type == "knight" || (type == "king" && w < king->GetCol() - 1)){
					safeWest = true;
				}else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Checker::CheckNwSe(bool isWhite){
	Position* king = (isWhite)? whiteKing: blackKing;
	bool safeNw = false;
	bool safeSe = false;
	for (int w = king->GetCol() - 1, e = king->GetCol() + 1,
			n = king->GetRow() - 1, s= king->GetRow() + 1;
			!safeNw || !safeSe; w--, e++, n--, s++){
		if (e > 7 || s > 7 || safeSe){
			safeSe = true;
		}else{

			Piece* sePiece = board->GetSquare(s, e)->GetOccupant();
			string type;
			if (sePiece != NULL){
				type = sePiece->GetType();
				if (sePiece->IsWhite() == isWhite || type == "rook" || type == "knight"
					|| (type == "king" && (e > king->GetCol() + 1 || s > king->GetRow() + 1))
					|| (type == "pawn" && isWhite)){
					safeSe = true;
				}else if (type == "pawn" && !isWhite){
					if (e > king->GetCol() + 1 || s > king->GetRow() + 1) {
						safeSe = true;
					}else{
						return true;
					}
				}else {
					return true;
				}
			}
		}

		if (w < 0 || n < 0 || safeNw){
			safeNw = true;
		}else{
			Piece* nwPiece = board->GetSquare(n, w)->GetOccupant();
			string type;
			if (nwPiece != NULL){
				type = nwPiece->GetType();
				if (nwPiece->IsWhite() == isWhite || type == "rook" || type == "knight"
					|| (type == "king" && (w < king->GetCol() - 1 || n < king->GetRow() - 1))
					|| (type == "pawn" && !isWhite)){
					safeNw = true;
				}else if (type == "pawn" && isWhite){
					if (w < king->GetCol() - 1 || n < king->GetRow() - 1) {
						safeNw = true;
					}else{
						return true;
					}
				}else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Checker::CheckNeSw(bool isWhite){
	Position* king = (isWhite)? whiteKing : blackKing;
	bool safeNe = false;
	bool safeSw = false;
	for (int w = king->GetCol() - 1, e = king->GetCol() + 1,
			n = king->GetRow() - 1, s= king->GetRow() + 1;
			!safeNe || !safeSw; w--, e++, n--, s++){
		if (e > 7 || n < 0 || safeNe){
			safeNe = true;
		}else{
			Piece* nePiece = board->GetSquare(n, e)->GetOccupant();
			string type;
			if (nePiece != NULL){
				type = nePiece->GetType();;
				if (nePiece->IsWhite() == isWhite || type == "rook" || type == "knight"
					|| (type == "king" && (e > king->GetCol() + 1 || n < king->GetRow() - 1))
					|| (type == "pawn" && !isWhite)){
					safeNe = true;
				}else if (type == "pawn" && isWhite){
					if (e > king->GetCol() + 1 || n < king->GetRow() - 1) {
						safeNe = true;
					}else{
						return true;
					}
				}else {
					return true;
				}
			}
		}

		if (w < 0 || s > 7 || safeSw){
			safeSw = true;
		}else{
			Piece* swPiece = board->GetSquare(s, w)->GetOccupant();
			string type;
			if (swPiece != NULL){
				type = swPiece->GetType();
				if (swPiece->IsWhite() == isWhite || type == "rook" || type == "knight"
					|| (type == "king" && (w < king->GetCol() - 1 || s > king->GetRow() + 1))
					|| (type == "pawn" && isWhite)){
					safeSw = true;
				}else if (type == "pawn" && !isWhite){
					if (w < king->GetCol() - 1 || s > king->GetRow() + 1) {
						safeSw = true;
					}else{
						return true;
					}
				}else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Checker::CheckKnight(bool isWhite){
	Position* king;
	if (isWhite){
		king = whiteKing;
	}else{
		king = blackKing;
	}
	Piece* possibleKnight = NULL;
	int validRow;
	int validCol;

	for (int s = -2; s <= 2; s++){
		int e;
		if (s == 0){continue;}
		e = (s % 2 != 0)? 2 : 1;
		possibleKnight = NULL;
		validRow = king->GetRow() + s;
		validCol = king->GetCol() - e;
		if (validRow >= 0 && validRow <=7 && validCol >= 0 && validCol <= 7){
			possibleKnight = board->GetSquare(validRow, validCol)->GetOccupant();
		}
		if (possibleKnight){
			if (possibleKnight->IsWhite() != isWhite && possibleKnight->GetType() == "knight"){
				return true;
			}
		}

		possibleKnight = NULL;
		validRow = king->GetRow() + s;
		validCol = king->GetCol() + e;
		if (validRow >= 0 && validRow <=7 && validCol >= 0 && validCol <= 7){
			possibleKnight = board->GetSquare(validRow, validCol)->GetOccupant();
		}
		if (possibleKnight){
			if (possibleKnight->IsWhite() != isWhite && possibleKnight->GetType() == "knight"){
				return true;
			}
		}
	}
	return false;
}

bool Checker::Test(std::ostream& os){
	bool success = true;
	os << "Testing Checker..." << endl;
	Board* board = new Board();
	Checker c(board);
	c.UpdatePosition(true, new Position(7, 4));
	TEST(!c.IsInCheck(true));
	board->GetSquare(3,4)->ChangeOccupant(new Pawn (true));
	TEST(!c.IsInCheck(true));
	board->GetSquare(4,4)->ChangeOccupant(new Queen (true));
	TEST(!c.IsInCheck(true));
	board->GetSquare(4,4)->ChangeOccupant(new Queen (false));
	TEST(c.IsInCheck(true));
	c.UpdatePosition(true, new Position(0, 4));
	TEST(!c.IsInCheck(true));
	board->GetSquare(3,4)->ChangeOccupant(NULL);
	TEST(c.IsInCheck(true));

	delete board;

	board = new Board();

	c.UpdatePosition(true, new Position(7, 2));
	TEST(!c.IsInCheck(true));
	board->GetSquare(7,6)->ChangeOccupant(new Pawn (true));
	TEST(!c.IsInCheck(true));
	board->GetSquare(7,5)->ChangeOccupant(new Queen (true));
	TEST(!c.IsInCheck(true));
	board->GetSquare(7,5)->ChangeOccupant(new Queen (false));
	TEST(c.IsInCheck(true));
	c.UpdatePosition(true, new Position(7, 7));
	TEST(!c.IsInCheck(true));
	board->GetSquare(7,6)->ChangeOccupant(NULL);
	TEST(c.IsInCheck(true));
	c.UpdatePosition(false, new Position(7,6));
	TEST(c.IsInCheck(true));

	delete board;
	board = new Board();

	c.UpdatePosition(true, new Position(3, 3));
	TEST(!c.IsInCheck(true));
	board->GetSquare(6,6)->ChangeOccupant(new Queen (false));
	TEST(c.IsInCheck(true));
	board->GetSquare(4,4)->ChangeOccupant(new Pawn (false));
	TEST(!c.IsInCheck(true));
	c.UpdatePosition(false, new Position(0, 0));
	TEST(!c.IsInCheck(false));
	board->GetSquare(1,1)->ChangeOccupant(new Pawn (true));
	TEST(c.IsInCheck(false));

	delete board;
	board = new Board();
	c.UpdatePosition(true, new Position(4, 4));
	TEST(!c.IsInCheck(true));
	board->GetSquare(0,0)->ChangeOccupant(new Queen (false));
	TEST(c.IsInCheck(true));
	board->GetSquare(1,1)->ChangeOccupant(new Pawn (false));
	TEST(!c.IsInCheck(true));
	board->GetSquare(5,5)->ChangeOccupant(new Pawn (false));
	TEST(!c.IsInCheck(true));
	board->GetSquare(3,3)->ChangeOccupant(new Pawn (false));
	TEST(c.IsInCheck(true));

	delete board;
	board = new Board();

	c.UpdatePosition(true, new Position(3, 3));
	TEST(!c.IsInCheck(true));
	board->GetSquare(0,6)->ChangeOccupant(new Queen (false));
	TEST(c.IsInCheck(true));
	board->GetSquare(1,5)->ChangeOccupant(new Pawn (false));
	TEST(!c.IsInCheck(true));
	board->GetSquare(2,4)->ChangeOccupant(new Pawn (false));
	TEST(c.IsInCheck(true));

	delete board;
	board = new Board();

	c.UpdatePosition(false, new Position(3, 3));
	TEST(!c.IsInCheck(false));
	board->GetSquare(6,0)->ChangeOccupant(new Queen (true));
	TEST(c.IsInCheck(false));
	board->GetSquare(5,1)->ChangeOccupant(new Pawn (false));
	TEST(!c.IsInCheck(false));
	board->GetSquare(4,2)->ChangeOccupant(new Pawn (true));
	TEST(c.IsInCheck(false));

	delete board;
	board = new Board();
	board->GetSquare(3,3)->ChangeOccupant(new King(WHITE));
	c.UpdatePosition(WHITE, new Position(3,3));
	TEST(!c.IsInCheck(true));
	board->GetSquare(1,2)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(1,2)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(2,1)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(2,1)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(4,1)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(4,1)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(5,2)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(5,2)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(5,4)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(5,4)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(4,5)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(4,5)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(2,5)->ChangeOccupant(new Knight(false));
	TEST(c.IsInCheck(true));
	board->GetSquare(2,5)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(true));

	board->GetSquare(1,4)->ChangeOccupant(new Knight(BLACK));
	TEST(c.IsInCheck(true));
	board->GetSquare(1,4)->ChangeOccupant(new Knight(true));
	TEST(!c.IsInCheck(WHITE));

	return success;
}

