home    = /home/courses/cop4530p/spring14
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
tests   = $(home)/tests
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
CC      = g++47 -std=c++11 -Wall -Wextra

project: wb2.x foaa.x moaa.x

foaa.x:  foaa.o xstring.o
	$(CC) -o foaa.x foaa.o xstring.o

foaa.o : foaa.cpp oaa.h
	$(CC) $(incpath) -c $(proj)/foaa.cpp

wb2.x:   main2.o xstring.o wordbench2.o
	$(CC) -o wb2.x main2.o xstring.o wordbench2.o

main2.o: $(proj)/wordbench2.h $(proj)/main2.cpp
	$(CC) $(incpath)  -c $(proj)/main2.cpp

wordbench2.o: $(proj)/wordbench2.h $(proj)/wordbench2.cpp
	$(CC) $(incpath)  -c wordbench2.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp

