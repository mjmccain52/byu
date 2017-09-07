#include "MyController.h"
#include <time.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void MyController::on_CellSelected(int row, int col, int button){
	/*
	 * If a piece hasn't been previously clicked on, highlight the moves of the piece
	 * clicked on, if valid
	 */
	if (!facade->HavePiece()){
		if (facade->ClickedYourPiece(row, col)){
			view->HighlightSquare(row, col, BLUE_SQUARE);
			set<Position*>* moves = facade->GetCurrentValidMoves();
			set<Position*>::iterator it;
			for (it=moves->begin(); it!=moves->end(); it++){
				view->HighlightSquare((*it)->GetRow(), (*it)->GetCol(), GREEN_SQUARE);
			}
		}
	}
	/*
	 * If a valid move was selected, draw that move on the board
	 */
	else{

		Position* p = facade->GetSelectedSquare()->GetPosition();
		view->UnHighlightSquare(p->GetRow(), p->GetCol());
		set<Position*>* moves = facade->GetCurrentValidMoves();
		set<Position*>::iterator it;
		for (it=moves->begin(); it!=moves->end(); it++){
			if (row == (*it)->GetRow() && col == (*it)->GetCol()){
				Move* m = facade->MovePiece(row, col);
				Position* start = m->GetStart();
				Position* end = m->GetEnd();
				Piece* toPlace = m->GetMovedPiece();
				view->ClearPiece(start->GetRow(), start->GetCol());
				view->PlacePiece(end->GetRow(), end->GetCol(),
						GetPieceType(toPlace->GetType(), toPlace->IsWhite()));
			}
			view->UnHighlightSquare((*it)->GetRow(), (*it)->GetCol());
		}
		facade->ReleasePiece();
	}
	if(facade->IsCheck()){
		if (facade->NoValidMoves()){
			view->SetTopLabel("Checkmate!!");
		}else{
			view->SetTopLabel("Check!");
		}
	}else{
		(facade->NoValidMoves())? view->SetTopLabel("Stalemate!!") :
			view->SetTopLabel(facade->WhoseTurn() + "'s turn.");
	}
}

void MyController::on_DragStart(int row,int col){}

bool MyController::on_DragEnd(int row,int col) {return false;}

void MyController::on_NewGame(){
	view->ClearMessageArea();
	saveFile = "";
	facade = new Facade();
	Board* board = facade->NewGame();
	for (int i = 0; i < 8; i++ ){
		for (int j = 0; j < 8; j++){
			Piece* toPlace = board->GetSquare(i,j)->GetOccupant();
			Position* pos = board->GetSquare(i,j)->GetPosition();
			view->UnHighlightSquare(i,j);
			if (toPlace){

				view->PlacePiece(pos->GetRow(), pos->GetCol(),
						GetPieceType(toPlace->GetType(), toPlace->IsWhite()));
			}else{
				view->ClearPiece(pos->GetRow(), pos->GetCol());
			}
		}
	}
	view->SetTopLabel(facade->WhoseTurn() + "'s turn.");
}

void MyController::on_SaveGame(){
	if (saveFile.length() == 0){
		saveFile = view->SelectSaveFile();
	}
	if (saveFile.length() > 0){ //user might cancel save.
		facade->SaveGame(saveFile);
		view->SetStatusBar(saveFile);
		view->WriteMessageArea("Game saved.\n");
	}
}

void MyController::on_SaveGameAs(){
	string temp = view->SelectSaveFile();

	if (temp.length() > 0){ //user might cancel save.
		saveFile = temp;
		facade->SaveGame(saveFile);
		view->SetStatusBar(saveFile);
		view->WriteMessageArea("Game saved.\n");
	}
}

void MyController::on_LoadGame(){
	string temp = view->SelectLoadFile();
	if (temp.length() > 0){ //user might cancel load.
		try{
			saveFile = temp;
			Board* board = facade->LoadGame(saveFile);
			view->SetStatusBar(saveFile);
			for (int i = 0; i < 8; i++ ){
				for (int j = 0; j < 8; j++){
					Piece* toPlace = board->GetSquare(i,j)->GetOccupant();
					Position* pos = board->GetSquare(i,j)->GetPosition();
					view->UnHighlightSquare(i,j);
					if (toPlace){

						view->PlacePiece(pos->GetRow(), pos->GetCol(),
								GetPieceType(toPlace->GetType(), toPlace->IsWhite()));
					}else{
						view->ClearPiece(pos->GetRow(), pos->GetCol());
					}
				}
			}
			if(facade->IsCheck()){
				if (facade->NoValidMoves()){
					view->SetTopLabel("Checkmate!!");
				}else{
					view->SetTopLabel("Check!");
				}
			}else{
				if (facade->NoValidMoves()){
					view->SetTopLabel("Stalemate!!");
				}
				else{
					view->SetTopLabel(facade->WhoseTurn() + "'s turn.");
				}
			}
			view->WriteMessageArea("Game loaded.\n");
		}catch (...){
			view->WriteMessageArea("Error loading file.\n");
		}
	}


}

void MyController::on_UndoMove(){
	Move* m = facade->UndoMove();
	if (m){
		Position* start = m->GetStart();
		Position* end = m->GetEnd();
		Piece* moved = m->GetMovedPiece();
		Piece* taken = m->GetTakenPiece();
		view->PlacePiece(start->GetRow(), start->GetCol(),
				GetPieceType(moved->GetType(), moved->IsWhite()));
		if (taken){
			view->PlacePiece(end->GetRow(), end->GetCol(),
					GetPieceType(taken->GetType(), taken->IsWhite()));
		}else{
			view->ClearPiece(end->GetRow(), end->GetCol());
		}
		view->SetTopLabel(facade->WhoseTurn() + "'s turn.");
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				view->UnHighlightSquare(i,j);
			}
		}
		if(facade->IsCheck()){
			if (facade->NoValidMoves()){
				view->SetTopLabel("Checkmate!!");
			}else{
				view->SetTopLabel("Check!");
			}
		}else{
			(facade->NoValidMoves())? view->SetTopLabel("Stalemate!!") :
				view->SetTopLabel(facade->WhoseTurn() + "'s turn.");
		}

	}
}

void MyController::on_QuitGame(){}

void MyController::on_TimerEvent() {}

void MyController::SetView(ChessView* view) {
	this->view = view;
}

ImageName MyController::GetPieceType(const std::string& type, bool isWhite){
	if (isWhite){
		return GetWhiteType(type);
	}else{
		return GetBlackType(type);
	}

	return NO_IMAGE;
}

ImageName MyController::GetWhiteType(const std::string& type){
	ImageName toReturn = NO_IMAGE;
	if (type == "pawn"){
		toReturn = W_PAWN;
	}else if (type == "rook"){
		toReturn = W_ROOK;
	}else if (type == "knight"){
		toReturn = W_KNIGHT;
	}else if (type == "bishop"){
		toReturn = W_BISHOP;
	}else if (type == "queen"){
		toReturn = W_QUEEN;
	}else if (type == "king"){
		toReturn = W_KING;
	}
	return toReturn;
}
ImageName MyController::GetBlackType(const std::string& type){
	ImageName toReturn = NO_IMAGE;
	if (type == "pawn"){
		toReturn = B_PAWN;
	}else if (type == "rook"){
		toReturn = B_ROOK;
	}else if (type == "knight"){
		toReturn = B_KNIGHT;
	}else if (type == "bishop"){
		toReturn = B_BISHOP;
	}else if (type == "queen"){
		toReturn = B_QUEEN;
	}else if (type == "king"){
		toReturn = B_KING;
	}
	return toReturn;
}
void MyController::SetupNewGame(bool comp1, bool comp2){

}

void MyController::TakeComputersTurn(){

}
