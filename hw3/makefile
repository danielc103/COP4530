home    = /home/courses/cop4530p/spring14
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
tests   = $(home)/tests
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
CC      = g++47 -std=c++11 -Wall -Wextra

project: wb.x

wb.x:   main.o xstring.o wordbench.o
	$(CC) -o wb.x main.o xstring.o wordbench.o

main.o: $(proj)/wordbench.h $(proj)/main.cpp
	$(CC) $(incpath)  -c $(proj)/main.cpp

wordbench.o: $(proj)/wordbench.h $(proj)/wordbench.cpp
	$(CC) $(incpath)  -c wordbench.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp
