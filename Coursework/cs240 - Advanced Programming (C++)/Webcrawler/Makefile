
#** Variables **#
BIN_FILE = bin/crawler

OBJ_FILES = obj/Crawler.o obj/Occurrences.o obj/WordIndex.o obj/PageQueue.o obj/StopWords.o \
		obj/OutputGenerator.o obj/Page.o obj/Pages.o obj/URL.o obj/URLFilter.o obj/HTMLParser.o \
		obj/Webcrawler.o obj/PageDownloader.o

TEST_BIN_FILE = test/crawler-tests

TEST_OBJ_FILES = obj/Crawler-Tests.o obj/Occurrences.o obj/WordIndex.o obj/PageQueue.o \
		obj/StopWords.o obj/OutputGenerator.o obj/Page.o obj/Pages.o obj/URL.o obj/URLFilter.o \
		obj/HTMLParser.o obj/Webcrawler.o obj/PageDownloader.o

LIB = lib/libcs240utils.a

LIB_OBJ_FILES = utils/obj/StringUtil.o utils/obj/URLInputStream.o utils/obj/FileInputStream.o \
		utils/obj/HTTPInputStream.o utils/obj/CommandRunner.o utils/obj/FileSystem.o \
		utils/obj/HTMLTokenizer.o utils/obj/HTMLToken.o

C_FLAGS = -c -Wall -I inc

LIB_C_FLAGS = -c -Wall -I utils/include/

LIB_H_FILES = -I utils/include

#** Pseudotargets **#
bin: $(BIN_FILE)

test: $(TEST_BIN_FILE)
	$(TEST_BIN_FILE)

valgrind: $(TEST_BIN_FILE)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes \
		--suppressions=test/string.supp $(TEST_BIN_FILE)

debug: $(TEST_BIN_FILE)
	ddd $(TEST_BIN_FILE) &
	
lib: $(LIB)

style:
	~cs240ta/bin/CppCheckStyle/CppCheckStyle src/Occurrences.cpp src/WordIndex.cpp src/PageQueue.cpp src/StopWords.cpp \
		src/OutputGenerator.cpp src/Page.cpp src/Pages.cpp src/URL.cpp src/URLFilter.cpp src/HTMLParser.cpp src/PageDownloader.cpp src/Webcrawler.cpp\
	 	inc/Occurrences.h inc/WordIndex.h inc/PageQueue.h inc/StopWords.h \
	 	inc/OutputGenerator.h inc/Page.h inc/Pages.h inc/URL.h inc/URLFilter.h inc/HTMLParser.h inc/PageDownloader.h inc/Webcrawler.h
	
clean: 
		@rm -f $(BIN_FILE)
		@rm -f $(TEST_BIN_FILE)
		@rm -f obj/*.o
		@rm -f utils/obj/*.o
		@rm -f $(LIB)
		@echo "cleaned house" 

#** Targets **#
$(LIB) : $(LIB_OBJ_FILES)
	ar r $(LIB) $(LIB_OBJ_FILES)
	
$(BIN_FILE) : $(OBJ_FILES) $(LIB)
	g++ -o $(BIN_FILE) $(OBJ_FILES) $(LIB)
	@chmod a+x $(BIN_FILE)
	
$(TEST_BIN_FILE) : $(TEST_OBJ_FILES) $(LIB)
	g++ -g -o $(TEST_BIN_FILE) $(TEST_OBJ_FILES) $(LIB)
	@chmod a+x $(TEST_BIN_FILE)

obj/PageDownloader.o : src/PageDownloader.cpp inc/PageDownloader.h
	g++ $(C_FLAGS) -g -o obj/PageDownloader.o src/PageDownloader.cpp $(LIB_H_FILES)
	
obj/Webcrawler.o : src/Webcrawler.cpp inc/Webcrawler.h
	g++ $(C_FLAGS) -g -o obj/Webcrawler.o src/Webcrawler.cpp $(LIB_H_FILES)
	
obj/HTMLParser.o : src/HTMLParser.cpp inc/HTMLParser.h
	g++ $(C_FLAGS) -g -o obj/HTMLParser.o src/HTMLParser.cpp $(LIB_H_FILES)
	
obj/TreeIterator.o : src/TreeIterator.cpp inc/TreeIterator.h
	g++ $(C_FLAGS) -g -o obj/TreeIterator.o src/TreeIterator.cpp $(LIB_H_FILES)

obj/URLFilter.o : src/URLFilter.cpp inc/URLFilter.h
	g++ $(C_FLAGS) -g -o obj/URLFilter.o src/URLFilter.cpp $(LIB_H_FILES)

obj/URL.o : src/URL.cpp inc/URL.h
	g++ $(C_FLAGS) -g -o obj/URL.o src/URL.cpp $(LIB_H_FILES)

obj/Pages.o : src/Pages.cpp inc/Pages.h inc/Page.h
	g++ $(C_FLAGS) -g -o obj/Pages.o src/Pages.cpp $(LIB_H_FILES)
	
obj/Page.o : src/Page.cpp inc/Page.h
	g++ $(C_FLAGS) -g -o obj/Page.o src/Page.cpp $(LIB_H_FILES)
	
obj/OutputGenerator.o : src/OutputGenerator.cpp inc/OutputGenerator.h
	g++ $(C_FLAGS) -g -o obj/OutputGenerator.o src/OutputGenerator.cpp $(LIB_H_FILES)
		
obj/StopWords.o : src/StopWords.cpp inc/StopWords.h
	g++ $(C_FLAGS) -g -o obj/StopWords.o src/StopWords.cpp $(LIB_H_FILES)
	
obj/PageQueue.o : src/PageQueue.cpp inc/PageQueue.h
	g++ $(C_FLAGS) -g -o obj/PageQueue.o src/PageQueue.cpp $(LIB_H_FILES)

obj/Occurrences.o : src/Occurrences.cpp inc/Occurrences.h
	g++ $(C_FLAGS) -g -o obj/Occurrences.o src/Occurrences.cpp $(LIB_H_FILES)
	
obj/WordIndex.o : src/WordIndex.cpp inc/WordIndex.h inc/Occurrences.h
	g++ $(C_FLAGS) -g -o obj/WordIndex.o src/WordIndex.cpp $(LIB_H_FILES)
	
utils/obj/StringUtil.o : utils/src/StringUtil.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/StringUtil.o utils/src/StringUtil.cpp
	
utils/obj/URLInputStream.o : utils/src/URLInputStream.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/URLInputStream.o utils/src/URLInputStream.cpp
	
utils/obj/FileInputStream.o : utils/src/FileInputStream.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/FileInputStream.o utils/src/FileInputStream.cpp
	
utils/obj/HTTPInputStream.o : utils/src/HTTPInputStream.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/HTTPInputStream.o utils/src/HTTPInputStream.cpp

utils/obj/HTMLTokenizer.o : utils/src/HTMLTokenizer.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/HTMLTokenizer.o utils/src/HTMLTokenizer.cpp
	
utils/obj/HTMLToken.o : utils/src/HTMLToken.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/HTMLToken.o utils/src/HTMLToken.cpp
		
utils/obj/CommandRunner.o : utils/src/CommandRunner.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/CommandRunner.o utils/src/CommandRunner.cpp
	
utils/obj/FileSystem.o : utils/src/FileSystem.cpp
	g++ $(LIB_C_FLAGS) -o utils/obj/FileSystem.o utils/src/FileSystem.cpp
	
obj/Crawler.o : src/Crawler.cpp
	g++ $(C_FLAGS) -o obj/Crawler.o src/Crawler.cpp
	
obj/Crawler-Tests.o : src/Crawler-Tests.cpp
	g++ $(C_FLAGS) -o obj/Crawler-Tests.o src/Crawler-Tests.cpp
