#include "Facade.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "UnitTest.h"
#include "MoveHistory.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "XmlIO.h"

using namespace std;
Board* Facade::NewGame(){
	whitesTurn = true;
	history.ClearHistory();
	selected = NULL;
	currentValidMoves = NULL;
	board = new Board();
	pieceGrabbed = false;

	for (int i = 0; i < 8; i++){
		board->GetSquare(6, i)->ChangeOccupant(new Pawn(WHITE));
	}
	board->GetSquare(7,0)->ChangeOccupant(new Rook(WHITE));
	board->GetSquare(7,1)->ChangeOccupant(new Knight(WHITE));
	board->GetSquare(7,2)->ChangeOccupant(new Bishop(WHITE));
	board->GetSquare(7,3)->ChangeOccupant(new Queen(WHITE));
	board->GetSquare(7,4)->ChangeOccupant(new King(WHITE));
	board->GetSquare(7,5)->ChangeOccupant(new Bishop(WHITE));
	board->GetSquare(7,6)->ChangeOccupant(new Knight(WHITE));
	board->GetSquare(7,7)->ChangeOccupant(new Rook(WHITE));

	for (int i = 0; i < 8; i++){
		board->GetSquare(1, i)->ChangeOccupant(new Pawn(BLACK));
	}
	board->GetSquare(0,0)->ChangeOccupant(new Rook(BLACK));
	board->GetSquare(0,1)->ChangeOccupant(new Knight(BLACK));
	board->GetSquare(0,2)->ChangeOccupant(new Bishop(BLACK));
	board->GetSquare(0,3)->ChangeOccupant(new Queen(BLACK));
	board->GetSquare(0,4)->ChangeOccupant(new King(BLACK));
	board->GetSquare(0,5)->ChangeOccupant(new Bishop(BLACK));
	board->GetSquare(0,6)->ChangeOccupant(new Knight(BLACK));
	board->GetSquare(0,7)->ChangeOccupant(new Rook(BLACK));

	checks = new Checker(board);
	checks->UpdatePosition(WHITE, board->GetSquare(7,4)->GetPosition());
	checks->UpdatePosition(BLACK, board->GetSquare(0,4)->GetPosition());
	return board;
}

Board* Facade::LoadGame(const string& filename){
	history.ClearHistory();
	selected = NULL;
	currentValidMoves = NULL;
	board = new Board();
	board = XmlIO::ReadFromFile(board, &history, filename);
	whitesTurn = !history.LastMovedIsWhite();
	checks = new Checker(board);
	pieceGrabbed = false;

	/*find the kings*/
	for (int i = 0; i < 8; i++){
		for (int j = 0; j< 8; j++){
			Piece* p = board->GetSquare(i,j)->GetOccupant();
			Position* pos = board->GetSquare(i,j)->GetPosition();
			if (p){
				if (p->GetType()=="king"){

					checks->UpdatePosition(p->IsWhite(), pos);
				}
			}
		}
	}
	return board;
}

void Facade::SaveGame(const string& filename){

	MoveHistory temp = history;
	XmlIO::WriteToFile(board, &temp, filename);

}

Move* Facade::UndoMove(){
	Move* toUndo = history.UndoMove();
	if (toUndo){
		pieceGrabbed = false;
		selected = NULL;
		currentValidMoves = NULL;
		Position* start = toUndo->GetStart();
		Position* end = toUndo->GetEnd();
		Piece* moved = toUndo->GetMovedPiece();
		Piece* taken = toUndo->GetTakenPiece();
		board->GetSquare(start)->ChangeOccupant(moved);
		board->GetSquare(end)->ChangeOccupant(taken);
		if (moved->GetType() == "pawn" && moved->IsWhite() && start->GetRow() == 6){
			(dynamic_cast<Pawn*>(moved))->Reset();
		}
		if (moved->GetType() == "pawn" && !moved->IsWhite() && start->GetRow() == 1){
			(dynamic_cast<Pawn*>(moved))->Reset();
		}
		if (moved->GetType() == "king"){
			checks->UpdatePosition(!whitesTurn, start);
		}
		whitesTurn = !whitesTurn;
	}
	return toUndo;
}
bool Facade::HavePiece(){
	return pieceGrabbed;
}
bool Facade::ClickedYourPiece(int row, int col){
	Piece* temp = board->GetSquare(row, col)->GetOccupant();
	if (temp){
		if(temp->IsWhite() == whitesTurn){
			pieceGrabbed = true;
			selected = board->GetSquare(row, col);
			Piece* p = selected->GetOccupant();
			currentValidMoves = p->GetValidMoves(board, selected, checks);
			return true;
		}
	}
	return false;
}

void Facade::ReleasePiece(){
	pieceGrabbed = false;
	selected = NULL;
	currentValidMoves = NULL;
}
Square* Facade::GetSelectedSquare() {
		return selected;
}
set <Position*>* Facade::GetCurrentValidMoves(){
	return currentValidMoves;
}

Move* Facade::MovePiece(int row, int col){
	Square* end = board->GetSquare(row, col);
	Piece* taken = end->GetOccupant();
	Piece* moved = selected->GetOccupant();
	if (moved->GetType() == "pawn"){
		(dynamic_cast<Pawn*>(moved))->MoveFirst();
	}
	if (moved->GetType() == "king"){
		checks->UpdatePosition(whitesTurn, end->GetPosition());
	}
	selected->ChangeOccupant(NULL);
	end->ChangeOccupant(moved);
	Move* move = new Move(moved, taken, selected->GetPosition(), end->GetPosition());
	history.AddMove(move);
	whitesTurn = !whitesTurn;
	return move;
}

std::string Facade::WhoseTurn() const{
	if (whitesTurn){
		return "White";
	}
	return "Black";
}

bool Facade::IsCheck(){
	return checks->IsInCheck(whitesTurn);
}

bool Facade::NoValidMoves(){
	for (int i = 0; i < 8; i++ ){
		for (int j = 0; j < 8; j++){
			Piece* p = board->GetSquare(i,j)->GetOccupant();
			if (p){
				if (p->IsWhite() == whitesTurn){
					if (p->GetValidMoves(board, board->GetSquare(i,j), checks)->size() > 0){
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Facade::Test(std::ostream& os){
	bool success = true;
	os << "Testing Facade..." << endl;
	Facade* f = new Facade();
	Board* b = f->NewGame();
	TEST(b->GetSquare(7,3)->GetOccupant()->GetType() == "queen");
	return success;
}
