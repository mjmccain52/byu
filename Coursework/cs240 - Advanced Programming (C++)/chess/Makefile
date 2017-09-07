# -----------------------------------------------------------------------------
# Generic Variables
# -----------------------------------------------------------------------------
CC = g++
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

FLAGS = -I$(INC_FOLDER) -I$(VIEW_INC_FOLDER) -I$(MODEL_INC_FOLDER) -I$(UTILS_INC_FOLDER) -Wall -g -fPIC

#CFLAGS are the -I values needed to compile files using the GTKMM, SIGC, and
#LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`  -I$(IMAGES_FOLDER)

#LIBS are the paths to the static libraries for GTKMM, SIGC, and LIBGLADE needed
#for linking
LIBS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`

#LIB_FLAGS D_LOG_DOMAIN is used by g_log in the ChessGui library to seperate logging messages from the library
# from logging messages from the students code
#IMPORTANT: You must add a compiler option here for the library to be dynamic
LIB_FLAGS = -shared -DG_LOG_DOMAIN=\"ChessGui\" -fPIC

# -----------------------------------------------------------------------------
# Folder Variables
# -----------------------------------------------------------------------------
VIEW_FOLDER = view
VIEW_INC_FOLDER = $(VIEW_FOLDER)/inc
VIEW_SRC_FOLDER = $(VIEW_FOLDER)/src
VIEW_OBJ_FOLDER = $(VIEW_FOLDER)/obj
IMAGES_FOLDER = $(VIEW_FOLDER)/images

CONTROLLER_FOLDER = controller
SRC_FOLDER = $(CONTROLLER_FOLDER)/src
INC_FOLDER = $(CONTROLLER_FOLDER)/inc
OBJ_FOLDER = $(CONTROLLER_FOLDER)/obj

BIN_FOLDER = bin

MODEL_FOLDER = model
MODEL_SRC_FOLDER = $(MODEL_FOLDER)/src
MODEL_INC_FOLDER = $(MODEL_FOLDER)/inc
MODEL_OBJ_FOLDER = $(MODEL_FOLDER)/obj

UTILS_FOLDER = utils
UTILS_SRC_FOLDER = $(UTILS_FOLDER)/src
UTILS_INC_FOLDER = $(UTILS_FOLDER)/include
UTILS_OBJ_FOLDER = $(UTILS_FOLDER)/obj

TEST_FOLDER = test

# -----------------------------------------------------------------------------
# File Name Variables
# -----------------------------------------------------------------------------
#change this to a dynamic library name
LIBRARY= $(VIEW_FOLDER)/libcs240.so
EXE_NAME = $(BIN_FOLDER)/chess
TEST_NAME = $(TEST_FOLDER)/test

LIB_OBJ_FILES = $(VIEW_OBJ_FOLDER)/Chess.o $(VIEW_OBJ_FOLDER)/ChessGui.o \
		$(VIEW_OBJ_FOLDER)/ChessGuiBoard.o $(VIEW_OBJ_FOLDER)/ChessGuiBoardCell.o \
		$(VIEW_OBJ_FOLDER)/ChessGuiImages.o $(VIEW_OBJ_FOLDER)/SelectDialog.o

OBJ_FILES = $(OBJ_FOLDER)/MyController.o $(MODEL_OBJ_FOLDER)/Position.o \
		$(MODEL_OBJ_FOLDER)/Square.o $(MODEL_OBJ_FOLDER)/Board.o \
		$(MODEL_OBJ_FOLDER)/Piece.o $(MODEL_OBJ_FOLDER)/Pawn.o \
		$(MODEL_OBJ_FOLDER)/Facade.o $(MODEL_OBJ_FOLDER)/Checker.o \
		$(MODEL_OBJ_FOLDER)/Queen.o $(MODEL_OBJ_FOLDER)/King.o \
		$(MODEL_OBJ_FOLDER)/Knight.o $(MODEL_OBJ_FOLDER)/Move.o \
		$(MODEL_OBJ_FOLDER)/MoveHistory.o $(MODEL_OBJ_FOLDER)/Rook.o \
		$(MODEL_OBJ_FOLDER)/Bishop.o $(MODEL_OBJ_FOLDER)/XmlIO.o $(UTILS_OBJ_FILES)\

UTILS_OBJ_FILES = $(UTILS_OBJ_FOLDER)/StringUtil.o $(UTILS_OBJ_FOLDER)/URLInputStream.o \
		$(UTILS_OBJ_FOLDER)/FileInputStream.o $(UTILS_OBJ_FOLDER)/HTTPInputStream.o \
		$(UTILS_OBJ_FOLDER)/CommandRunner.o $(UTILS_OBJ_FOLDER)/FileSystem.o \
		$(UTILS_OBJ_FOLDER)/HTMLTokenizer.o $(UTILS_OBJ_FOLDER)/HTMLToken.o
		
EXE_OBJ_FILES = $(OBJ_FOLDER)/main.o $(OBJ_FILES)

TEST_OBJ_FILES = $(TEST_FOLDER)/TestSuite.o $(OBJ_FILES)

# -----------------------------------------------------------------------------
# Command Variables
# -----------------------------------------------------------------------------
bin : $(EXE_NAME)

run : $(EXE_NAME)
	./$(EXE_NAME) 0 0
	
runhh : $(EXE_NAME)
	./$(EXE_NAME) 0 0
	
runhc : $(EXE_NAME)
	./$(EXE_NAME) 0 1
	
runch : $(EXE_NAME)
	./$(EXE_NAME) 1 0
	
runcc : $(EXE_NAME)
	./$(EXE_NAME) 1 1
	
memtest: $(EXE_NAME)
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --suppressions=chess.supp $(EXE_NAME)
	
debug : $(EXE_NAME)
	gdb $(EXE_NAME)
	
lib : $(LIBRARY)

test : $(TEST_NAME)
	./$(TEST_NAME)

style:
	~cs240ta/bin/CppCheckStyle/CppCheckStyle \
	 $(SRC_FOLDER)/MyController.cpp $(MODEL_SRC_FOLDER)/Position.cpp  $(MODEL_SRC_FOLDER)/Square.cpp \
	 $(MODEL_SRC_FOLDER)/Board.cpp $(MODEL_SRC_FOLDER)/Piece.cpp $(MODEL_SRC_FOLDER)/Pawn.cpp \
	 $(MODEL_SRC_FOLDER)/Facade.cpp $(MODEL_SRC_FOLDER)/Checker.cpp $(MODEL_SRC_FOLDER)/Queen.cpp \
	 $(MODEL_SRC_FOLDER)/King.cpp $(MODEL_SRC_FOLDER)/Bishop.cpp $(MODEL_SRC_FOLDER)/Knight.cpp \
	 $(MODEL_SRC_FOLDER)/Rook.cpp $(MODEL_SRC_FOLDER)/Move.cpp $(MODEL_SRC_FOLDER)/MoveHistory.cpp \
	 $(MODEL_SRC_FOLDER)/XmlIO.cpp
	 
	 
clean: 
	-rm -f $(EXE_NAME)
	-rm -f $(EXE_OBJ_FILES)
	-rm -f $(SRC_FOLDER)/*~ $(INC_FOLDER)/*~
	-rm -f $(LIBRARY) $(LIB_OBJ_FILES)
	-rm -f $(VIEW_SRC_FOLDER)/*~ $(VIEW_INC_FOLDER)/*~

# -----------------------------------------------------------------------------
# File Construction
# -----------------------------------------------------------------------------
$(EXE_NAME): $(EXE_OBJ_FILES)  $(LIBRARY)
	$(CC) $(FLAGS) $(CFLAGS) $(LIBS) -o $(EXE_NAME) $(EXE_OBJ_FILES) $(LIBRARY) 
	
$(OBJ_FOLDER)/main.o: $(SRC_FOLDER)/main.cpp
	$(CC) -c $(FLAGS) $(CFLAGS) -o $(OBJ_FOLDER)/main.o $(SRC_FOLDER)/main.cpp
		
# Students: Place your makefile commands here
$(TEST_NAME): $(TEST_OBJ_FILES)  $(LIBRARY)
	$(CC) $(FLAGS) $(CFLAGS) $(LIBS) -o $(TEST_NAME) $(TEST_OBJ_FILES) $(LIBRARY) 
	
$(TEST_FOLDER)/TestSuite.o: $(TEST_FOLDER)/TestSuite.cpp
	$(CC) -c $(FLAGS) $(CFLAGS) -o $(TEST_FOLDER)/TestSuite.o $(TEST_FOLDER)/TestSuite.cpp

$(OBJ_FOLDER)/MyController.o : $(SRC_FOLDER)/MyController.cpp $(INC_FOLDER)/MyController.h $(INC_FOLDER)/ChessController.h
	$(CC) -c $(FLAGS) $(CFLAGS) -o $(OBJ_FOLDER)/MyController.o $(SRC_FOLDER)/MyController.cpp

$(MODEL_OBJ_FOLDER)/Position.o : $(MODEL_SRC_FOLDER)/Position.cpp $(MODEL_INC_FOLDER)/Position.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Position.o $(MODEL_SRC_FOLDER)/Position.cpp
	
$(MODEL_OBJ_FOLDER)/Square.o : $(MODEL_SRC_FOLDER)/Square.cpp $(MODEL_INC_FOLDER)/Square.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Square.o $(MODEL_SRC_FOLDER)/Square.cpp
	
$(MODEL_OBJ_FOLDER)/Board.o : $(MODEL_SRC_FOLDER)/Board.cpp $(MODEL_INC_FOLDER)/Board.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Board.o $(MODEL_SRC_FOLDER)/Board.cpp

$(MODEL_OBJ_FOLDER)/Piece.o : $(MODEL_SRC_FOLDER)/Piece.cpp $(MODEL_INC_FOLDER)/Piece.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Piece.o $(MODEL_SRC_FOLDER)/Piece.cpp

$(MODEL_OBJ_FOLDER)/Pawn.o : $(MODEL_SRC_FOLDER)/Pawn.cpp $(MODEL_INC_FOLDER)/Pawn.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Pawn.o $(MODEL_SRC_FOLDER)/Pawn.cpp
	
$(MODEL_OBJ_FOLDER)/Facade.o : $(MODEL_SRC_FOLDER)/Facade.cpp $(MODEL_INC_FOLDER)/Facade.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Facade.o $(MODEL_SRC_FOLDER)/Facade.cpp

$(MODEL_OBJ_FOLDER)/Checker.o : $(MODEL_SRC_FOLDER)/Checker.cpp $(MODEL_INC_FOLDER)/Checker.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Checker.o $(MODEL_SRC_FOLDER)/Checker.cpp

$(MODEL_OBJ_FOLDER)/Queen.o : $(MODEL_SRC_FOLDER)/Queen.cpp $(MODEL_INC_FOLDER)/Queen.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Queen.o $(MODEL_SRC_FOLDER)/Queen.cpp

$(MODEL_OBJ_FOLDER)/King.o : $(MODEL_SRC_FOLDER)/King.cpp $(MODEL_INC_FOLDER)/King.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/King.o $(MODEL_SRC_FOLDER)/King.cpp
	
$(MODEL_OBJ_FOLDER)/Knight.o : $(MODEL_SRC_FOLDER)/Knight.cpp $(MODEL_INC_FOLDER)/Knight.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Knight.o $(MODEL_SRC_FOLDER)/Knight.cpp

$(MODEL_OBJ_FOLDER)/Move.o : $(MODEL_SRC_FOLDER)/Move.cpp $(MODEL_INC_FOLDER)/Move.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Move.o $(MODEL_SRC_FOLDER)/Move.cpp
	
$(MODEL_OBJ_FOLDER)/MoveHistory.o : $(MODEL_SRC_FOLDER)/MoveHistory.cpp $(MODEL_INC_FOLDER)/MoveHistory.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/MoveHistory.o $(MODEL_SRC_FOLDER)/MoveHistory.cpp
	
$(MODEL_OBJ_FOLDER)/Rook.o : $(MODEL_SRC_FOLDER)/Rook.cpp $(MODEL_INC_FOLDER)/Rook.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Rook.o $(MODEL_SRC_FOLDER)/Rook.cpp
	
$(MODEL_OBJ_FOLDER)/Bishop.o : $(MODEL_SRC_FOLDER)/Bishop.cpp $(MODEL_INC_FOLDER)/Bishop.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/Bishop.o $(MODEL_SRC_FOLDER)/Bishop.cpp

$(MODEL_OBJ_FOLDER)/XmlIO.o : $(MODEL_SRC_FOLDER)/XmlIO.cpp $(MODEL_INC_FOLDER)/XmlIO.h
	$(CC) -c $(FLAGS) -o $(MODEL_OBJ_FOLDER)/XmlIO.o $(MODEL_SRC_FOLDER)/XmlIO.cpp
# Students: Place your makefile commands here

$(UTILS_OBJ_FOLDER)/StringUtil.o : $(UTILS_SRC_FOLDER)/StringUtil.cpp $(UTILS_INC_FOLDER)/StringUtil.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/StringUtil.o $(UTILS_SRC_FOLDER)/StringUtil.cpp

$(UTILS_OBJ_FOLDER)/URLInputStream.o : $(UTILS_SRC_FOLDER)/URLInputStream.cpp $(UTILS_INC_FOLDER)/URLInputStream.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/URLInputStream.o $(UTILS_SRC_FOLDER)/URLInputStream.cpp	

$(UTILS_OBJ_FOLDER)/FileInputStream.o : $(UTILS_SRC_FOLDER)/FileInputStream.cpp $(UTILS_INC_FOLDER)/FileInputStream.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/FileInputStream.o $(UTILS_SRC_FOLDER)/FileInputStream.cpp
	
$(UTILS_OBJ_FOLDER)/HTTPInputStream.o : $(UTILS_SRC_FOLDER)/HTTPInputStream.cpp $(UTILS_INC_FOLDER)/HTTPInputStream.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/HTTPInputStream.o $(UTILS_SRC_FOLDER)/HTTPInputStream.cpp
	
$(UTILS_OBJ_FOLDER)/HTMLTokenizer.o : $(UTILS_SRC_FOLDER)/HTMLTokenizer.cpp $(UTILS_INC_FOLDER)/HTMLTokenizer.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/HTMLTokenizer.o $(UTILS_SRC_FOLDER)/HTMLTokenizer.cpp
	
$(UTILS_OBJ_FOLDER)/HTMLToken.o : $(UTILS_SRC_FOLDER)/HTMLToken.cpp $(UTILS_INC_FOLDER)/HTMLToken.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/HTMLToken.o $(UTILS_SRC_FOLDER)/HTMLToken.cpp
	
$(UTILS_OBJ_FOLDER)/CommandRunner.o : $(UTILS_SRC_FOLDER)/CommandRunner.cpp $(UTILS_INC_FOLDER)/CommandRunner.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/CommandRunner.o $(UTILS_SRC_FOLDER)/CommandRunner.cpp

$(UTILS_OBJ_FOLDER)/FileSystem.o : $(UTILS_SRC_FOLDER)/FileSystem.cpp $(UTILS_INC_FOLDER)/FileSystem.h
	$(CC) -c $(FLAGS) -o $(UTILS_OBJ_FOLDER)/FileSystem.o $(UTILS_SRC_FOLDER)/FileSystem.cpp
# -----------------------------------------------------------------------------
# Library Construction
# -----------------------------------------------------------------------------
#This is currently a STATIC library, you must change it to a DYNAMIC library
#You must also add a compiler option to the variable LIB_FLAGS in order for the library to be dynamic
$(LIBRARY): $(LIB_OBJ_FILES) 
	$(CC) -shared -o $(LIBRARY) $(LIB_OBJ_FILES)
	#ar rcs $(LIBRARY) $(LIB_OBJ_FILES)

	
########DO NOT DELETE###########################################################################################3
#Below is some Makefile Magic to compile the libraries, you do not need to
#understand or alter it.  If you would like to, look up the Make manual online, it's very comprehensive	
LIBSOURCES = $(foreach file, $(shell ls $(VIEW_SRC_FOLDER)/*.cpp), $(basename $(notdir $(file))))

$(VIEW_OBJ_FOLDER)/%.o : $(VIEW_SRC_FOLDER)/%.cpp $(VIEW_INC_FOLDER)/Inline.h
	$(CC) $(FLAGS) $(LIB_FLAGS) $(CFLAGS) -c -o $@ $< 

  #The following is part of what lets us include Images within the binary. It currently only loads the default
  #"Image not found" icon that we use

INLINE_IMAGES = $(shell ls $(IMAGES_FOLDER)/* )
INLINE_IMAGE_PAIRS =$(foreach file, $(INLINE_IMAGES), $(basename $(notdir $(file)) $(file).* ))	
view/inc/Inline.h: $(INLINE_IMAGES)
	@echo "Updating Images"
	gdk-pixbuf-csource --raw --build-list $(INLINE_IMAGE_PAIRS) > $(VIEW_INC_FOLDER)/Inline.h

