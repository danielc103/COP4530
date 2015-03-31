home    = /home/courses/cop4530p/spring14
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
obj     = 
#CC      = g++ -Wall -Wextra
CC      = g++47 -std=c++11 -Wall -Wextra
all: mazetest.x ratpack.x

mazetest.x: mazetest.o maze.o
	$(CC) -o mazetest.x mazetest.o maze.o

ratpack.x: ratpack.o maze.o
	$(CC) -o ratpack.x ratpack.o maze.o

mazetest.o: mazetest.cpp maze.h
	$(CC) $(incpath)  -c mazetest.cpp

ratpack.o: ratpack.cpp maze.h
	$(CC) $(incpath)  -c ratpack.cpp

maze.o: maze.cpp maze.h
	$(CC) $(incpath)  -c maze.cpp
