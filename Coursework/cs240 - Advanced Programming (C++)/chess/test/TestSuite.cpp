#include "Board.h"
#include "Pawn.h"
#include "Square.h"
#include "Checker.h"
#include "Queen.h"
#include "King.h"
#include "Facade.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include <iostream>
using namespace std;

int main(){
	bool success = true;

	if (!Position::Test(cout)){success = false;}
	if (!Pawn::Test(cout)){success = false;}
	if (!Queen::Test(cout)){success = false;}
	if (!King::Test(cout)){success = false;}
	if (!Bishop::Test(cout)){success = false;}
	if (!Rook::Test(cout)){success = false;}
	if (!Knight::Test(cout)){success = false;}
	if (!Square::Test(cout)){success = false;}
	if (!Board::Test(cout)){success = false;}
	if (!Checker::Test(cout)){success = false;}
	if (!Facade::Test(cout)){success = false;}

	if (success){
			cout << "Tests succeeded." << endl;
	} else{
		cout << "Tests failed." << endl;
	}
	return 0;
}
