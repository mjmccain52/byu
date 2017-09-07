
#include "MoveHistory.h"

void MoveHistory::AddMove (Move* toAdd){
	moveHistory.push(toAdd);
}
Move* MoveHistory::UndoMove(){
	if (!moveHistory.empty()){
		Move* temp = moveHistory.top();
		moveHistory.pop();
		return temp;
	}
	return NULL;
}

void MoveHistory::ClearHistory(){
	while (!moveHistory.empty()){
		moveHistory.pop();
	}
}

bool MoveHistory::IsEmpty(){
	return moveHistory.empty();
}

MoveHistory& MoveHistory::operator= (MoveHistory& other){
	std::stack<Move*> reverse;
	ClearHistory();
	while (!other.moveHistory.empty()){
		reverse.push(other.moveHistory.top());
		other.moveHistory.pop();
	}
	while (!reverse.empty()){
		other.moveHistory.push(reverse.top());
		moveHistory.push(reverse.top());
		reverse.pop();
	}
	return *this;

}
