#ifndef CS240_XML_IO_H
#define CS240_XML_IO_H
#include "Board.h"
#include "MoveHistory.h"
#include <sstream>
#include <fstream>
#include <iostream>

class XmlIO{
public:

	//! Writes an xml document with information retrieved from the data structures.
	static void WriteToFile(Board* board, MoveHistory* history, const std::string& filename);

	//! ReadFromFile populates the data structures with info gleaned from an existing xml file
	static Board* ReadFromFile(Board* board, MoveHistory* history, const std::string& filename);

	static Piece* MakeNewPiece(const std::string& type, const std::string& color);
};

#endif
