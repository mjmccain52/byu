#ifndef CS240_FACADE_H
#define CS240_FACADE_H

#include <string>
#include <set>
#include "Move.h"
#include "Board.h"
#include "Checker.h"
#include "MoveHistory.h"

class Facade{
public:
	/** NEW GAME ALGORITHM **
		Clear Move History
		Clear Board Squares
		Reconfigure the squares in the board class
			-loop through square grid assigning color/position
			-loop for white/black pawns
		Draw GUI based on data structures
		Assign turn to the white player
	**/
	Board* NewGame();

	/** LOAD GAME ALGORITHM **
		Clear Move History
		Clear Board Squares
		Reconfigure the squares in the board class
			-loop through square grid assigning color/position
		Load Xml data into structures with XmlIO's Read function
			-using the xml tokenizer find the start board tag
			-while next token is start and piece
				get the column and row attributes
				use these to get the proper square from the board structure
				get the type and color attributes
				make a new piece with these
				change the occupant to be this guy on the square retrieved
			-find start tag of history
			-while next token is start and move
				create new move object based on the 2-3 pieces within the move block
				push move object onto the move history stack
		Draw GUI
	**/
	Board* LoadGame(const std::string& filename);

	/** SAVE GAME ALGORITHM **
		Write move history and board configuration into xml file.
			-open chess game tag
			-open board tag
			-for each square on the board
				-if the square is occupado
					-open piece tag
					-write the piece type, color, position
					-close piece tag
			-close board tag
			-open history tag
			-while history isn't empty
				-pop a move from the history stack
				-open move tag
				-open piece tag
				-write information from start piece
				-close piece tag
				-repeat this for end piece.
				-if a piece was taken
					-write info for taken piece
			-close history tag
			-close chess game tag
	**/
	void SaveGame(const std::string& filename);

	/** UNDO MOVE ALGORITHM
		Pop the last move from the history stack
		locate the end board position of the move with Move::GetEnd()
		Get the piece associated with this position
		locate the start board position of the move with Move::GetStart()
		update the start position on the board to have the piece in question
		if the move has a piece taken, place it on the end position.

		if the opponent is a computer and its human's turn
			-repeat this entire process (two undos to get back to your turn)

		Update the GUI
	**/
	Move* UndoMove();

	/** MOVE PIECE ALGORITHM
		if destination square is a valid move
			-Create a new move object with the information regarding the move
			and put it on the move history stack
			-using the same move object, update the squares on the board with the
			new piece
		-clear valid move set
		update GUI

	**/
	Move* MovePiece(int row, int col);

	//! Determines whether the king of the current player is in check
	bool IsCheck();

	//! Determines whether the king of the current player is in checkmate
	bool NoValidMoves();

	//! Determines whether there are not any valid moves to be made.
	bool IsStaleMate();

	bool ClickedYourPiece(int row, int col);
	bool HavePiece();
	void ReleasePiece();
	std::set <Position*>* GetCurrentValidMoves();
	Square* GetSelectedSquare();
	std::string WhoseTurn() const;
	static bool Test(std::ostream& os);

private:
	bool whitesTurn;
	bool pieceGrabbed;
	std::set <Position*>* currentValidMoves; //Populates itself every time a piece is selected
	Square* selected;
	bool check;
	bool checkmate;
	bool stalemate;
	Board* board;
	Checker* checks;
	MoveHistory history;
};

#endif
