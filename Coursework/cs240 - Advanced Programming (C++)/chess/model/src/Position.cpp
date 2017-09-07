#include "Position.h"
#include "UnitTest.h"
using namespace std;
Position::Position(int x, int y) : row(x), col(y){}

int Position::GetRow(){
	return row;
}

int Position::GetCol(){
	return col;
}

bool Position::Test(std::ostream& os){
	bool success = true;
	os << "Testing Position..." << endl;
	Position p(4,0);
	TEST(p.GetRow() == 4 && p.GetCol() == 0);

	return success;
}
