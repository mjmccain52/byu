#ifndef CS240_BOARD_H
#define CS240_BOARD_H

#define WHITE 1
#define BLACK 0

#include "Square.h"
#include <vector>

//! Board contains all the squares, which in turn contain the occupying pieces
class Board{
public:
	Board();
	Square* GetSquare(int row, int col);
	Square* GetSquare(Position* p);

	static bool Test(std::ostream& os);
private:
	std::vector< std::vector<Square*> > squares; //! 2-Dimensional vector holds all the board's squares
};

#endif
