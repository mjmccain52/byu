#ifndef CS240_MY_CONTROLLER_H
#define CS240_MY_CONTROLLER_H
#include "ChessController.h"
#include "Facade.h"
#include <iostream>

 class MyController : public ChessController {
 public:

		//! Called whenever any square is clicked on
	 	void on_CellSelected(int row, int col, int button);

	 	//!unimplemented
	 	void on_DragStart(int row,int col);

	 	//!unimplemented
	 	bool on_DragEnd(int row,int col);

	 	//!Calls new game on the facade and initializes the GUI for a new game
	 	void on_NewGame();

	 	//!Calls SaveGame on the facade, asking for a filename only the first time
	 	void on_SaveGame();

	 	//!Calls SaveGame on the facade, asking for a filename each time.
	 	void on_SaveGameAs();

	 	//!Calls LoadGame on the facade, passing in the filename requested
	 	void on_LoadGame();

	 	void on_UndoMove();

	 	void on_QuitGame();

	 	void on_TimerEvent();

	 	void SetView(ChessView* view);

	 	void SetupNewGame(bool comp1, bool comp2);

 private:
	 ImageName GetPieceType(const std::string& type, bool isWhite);
	 ImageName GetWhiteType(const std::string& type);
	 ImageName GetBlackType(const std::string& type);
	 void TakeComputersTurn();
	 ChessView* view;
	 Facade* facade;
	 std::string saveFile;
 };
#endif
