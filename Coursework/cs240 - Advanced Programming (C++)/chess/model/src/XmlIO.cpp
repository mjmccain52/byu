#include "XmlIO.h"
#include <fstream>
#include <sstream>
#include "HTMLTokenizer.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "UnitTest.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include <stdlib.h>
#include <ctype.h>
using namespace std;

void XmlIO::WriteToFile(Board* board, MoveHistory* history, const string& filename){
	ofstream xmlFile;
	xmlFile.open(filename.c_str());
	xmlFile << "<chessgame>" << endl;
	xmlFile << "<board>" << endl;
	Piece* p;
	for (int r = 0; r < 8; r++){
		for (int c = 0; c < 8; c++){
			p = board->GetSquare(r,c)->GetOccupant();
			if (p){
				xmlFile << "<piece type=\"" << p->GetType() << "\" color=\"";
				if (p->IsWhite()){
					xmlFile << "white\" row=\"";
				}else{
					xmlFile << "black\" row=\"";
				}
				xmlFile << r << "\" column=\"" << c << "\"/>"<< endl;
			}
		}
	}
	xmlFile << "</board>"<< endl;
	xmlFile << "<history>"<< endl;
	Move* m;
	string historyString = "";
	while (!history->IsEmpty()){
		m = history->UndoMove();
		Position* start = m->GetStart();
		Position* end = m->GetEnd();
		Piece* moved = m->GetMovedPiece();
		Piece* taken = m->GetTakenPiece();
		string type = moved->GetType();
		string color = "black";
		string otherColor = "white";
		if (moved->IsWhite()){
			color = "white";
			otherColor = "black";
		}
		ostringstream stream;
		stream << "<move>\n<piece type=\"" << type << "\" color=\"" << color
			<< "\" row=\""<< start->GetRow() << "\" column=\"" << start->GetCol() << "\"/>" << endl
			<< "<piece type=\"" << type << "\" color=\"" << color
			<< "\" row=\""<< end->GetRow() << "\" column=\"" << end->GetCol() << "\"/>"<< endl;
		if (taken){
			stream << "<piece type=\"" << taken->GetType() << "\" color=\"" << otherColor
			<< "\" row=\""<< end->GetRow() << "\" column=\"" << end->GetCol() << "\"/>"<< endl;
		}
		stream << "</move>"<< endl;
		historyString = stream.str() + historyString;
	}
	xmlFile << historyString;
	xmlFile << "</history>"<< endl;
	xmlFile << "</chessgame>" << endl;
	xmlFile.close();
}

Board* XmlIO::ReadFromFile(Board* board, MoveHistory* history, const string& filename){
	ifstream fileStream;
	fileStream.open(filename.c_str());
	string fileString = "";
	bool rightKindaFile = false;
	while (fileStream.good()){
		char got = fileStream.get();
		if (!isspace(got) || got == ' '){
			fileString += got;
		}
	}
	fileString = fileString.substr(0, fileString.length() - 1);
	HTMLTokenizer tokener(fileString);
	while(tokener.HasNextToken()){

		HTMLToken current(tokener.GetNextToken());
		string value = current.GetValue();
		if (!rightKindaFile){
			if (current.GetType() == TAG_START && value == "chessgame"){
				rightKindaFile = true;
				board = new Board();
				history->ClearHistory();
			}else{
				throw exception();
			}
		}
		if (current.GetType() == TAG_START && value == "board"){
			current = tokener.GetNextToken();
			if (current.GetType() == TEXT){
				current = tokener.GetNextToken();
			}
			while (current.GetValue() == "piece"){
				string type = current.GetAttribute("type");
				string color = current.GetAttribute("color");
				int row = atoi(current.GetAttribute("row").c_str());
				int col = atoi(current.GetAttribute("column").c_str());
				board->GetSquare(row, col)->ChangeOccupant(XmlIO::MakeNewPiece(type, color));
				current = tokener.GetNextToken();
				if (current.GetType() == TEXT){
					current = tokener.GetNextToken();
				}
			}
		}
		if (current.GetType() == TAG_START && value == "history"){
			current = tokener.GetNextToken();
			while (current.GetValue() != "history"){
				if (current.GetType() == TAG_START && current.GetValue() == "move"){
					Piece* moved;
					Piece* taken = NULL;
					Position* start;
					Position* end;
					string type;
					string color;
					int row;
					int col;

					current = tokener.GetNextToken();
					type = current.GetAttribute("type");
					color = current.GetAttribute("color");
					row = atoi(current.GetAttribute("row").c_str());
					col = atoi(current.GetAttribute("column").c_str());
					moved = XmlIO::MakeNewPiece(type, color);
					start = board->GetSquare(row,col)->GetPosition();

					current = tokener.GetNextToken();
					row = atoi(current.GetAttribute("row").c_str());
					col = atoi(current.GetAttribute("column").c_str());
					end = board->GetSquare(row,col)->GetPosition();

					current = tokener.GetNextToken();
					if (current.GetValue() == "piece"){
						type = current.GetAttribute("type");
						color = current.GetAttribute("color");
						taken = XmlIO::MakeNewPiece(type, color);
						current = tokener.GetNextToken();
					}
					history->AddMove(new Move(moved, taken, start, end));
				}else{
					current = tokener.GetNextToken();
				}
			}
		}
	}
	return board;
}

Piece* XmlIO::MakeNewPiece(const std::string& type, const std::string& color){
	Piece* newPiece;
	bool w = (color == "white");
	if (type == "pawn"){
		newPiece = new Pawn(w);
	}else if (type == "rook"){
		newPiece = new Rook(w);
	}else if (type == "knight"){
		newPiece = new Knight(w);
	}else if (type == "bishop"){
		newPiece = new Bishop(w);
	}else if (type == "queen"){
		newPiece = new Queen(w);
	}else{
		newPiece = new King(w);
	}
	return newPiece;

}
