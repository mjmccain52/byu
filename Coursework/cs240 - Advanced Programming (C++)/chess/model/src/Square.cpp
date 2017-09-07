#include "Pawn.h" // for testing
#include "Square.h"
#include "UnitTest.h"
using namespace std;

Square::Square(Position* pos, Piece* piece):
		position(pos), occupant(piece){}

void Square::ChangeOccupant(Piece* newOccupant){
	occupant = newOccupant;
}

Position* Square::GetPosition() const{
	return position;
}
Piece* Square::GetOccupant() const{
	return occupant;
}

bool Square::Test(ostream& os){
	bool success = true;
	os << "Testing Square..." << endl;
	Square s(new Position (1,2), NULL);
	TEST(s.GetPosition()->GetRow() == 1  && s.GetPosition()->GetCol() == 2);
	TEST(s.GetOccupant() == NULL);
	s.ChangeOccupant(new Pawn(false)); //black pawn
	TEST(s.GetOccupant()->GetType() == "pawn" && !s.GetOccupant()->IsWhite());
	return success;
}
