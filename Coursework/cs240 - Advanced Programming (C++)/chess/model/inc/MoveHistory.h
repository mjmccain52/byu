#ifndef CS240_MOVE_HISTORY_H
#define CS240_MOVE_HISTORY_H

#include<stack>
#include "Move.h"

class MoveHistory{
public:
	//! Accessor for private data
	//std::stack<Move*>* GetMoveHistory() const;
	//! Pushes a Move onto history
	void AddMove (Move* toAdd);
	//! Removes the last move from history--for cheaters only
	Move* UndoMove();
	//! Wipe the history clean.  Invoked at new games.
	void ClearHistory();

	bool IsEmpty();

	bool LastMovedIsWhite(){return moveHistory.top()->GetMovedPiece()->IsWhite();}
	MoveHistory& operator= (MoveHistory& other);

private:
	std::stack<Move*> moveHistory; //! Contains all the moves completed up to current point in game
};
#endif
