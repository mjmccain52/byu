#include "Board.h"
#include "UnitTest.h"
using namespace std;

Board::Board(){
	for (int i = 0; i < 8; i++){
		vector<Square*> temp;
		squares.push_back(temp);
		for (int j = 0; j < 8; j++){
			squares[i].push_back (new Square(new Position(i,j), NULL));
		}
	}
}

Square* Board::GetSquare(int row, int col){
	return squares[row][col];
}

Square* Board::GetSquare(Position* p){
	return squares[p->GetRow()][p->GetCol()];
}
bool Board::Test (ostream& os){
	bool success = true;
	os << "Testing Board..." << endl;
	Board b;
	Square* temp = b.GetSquare(3, 4);
	TEST(temp->GetPosition()->GetRow() == 3);
	TEST(temp->GetPosition()->GetCol() == 4);
	TEST(temp->GetOccupant() == NULL);
	return success;
}

