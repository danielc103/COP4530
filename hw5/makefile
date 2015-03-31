
home = /home/courses/cop4530p/spring14
cpp  = $(home)/cpp
tcpp = $(home)/tcpp

CC = g++47 -std=c++11 -I. -I$(cpp) -I$(tcpp) -Wall -Wextra

all:   mxv.x mxm.x smxsv.x smxsm.x m2sm.x sm2m.x \
       fhtbl.x rantable.x

mxm.x : matrix.h matrix_util.h mxm.cpp
	$(CC) -omxm.x mxm.cpp

mxv.x : matrix.h matrix_util.h mxv.cpp
	$(CC) -omxv.x mxv.cpp

smxsm.x : sparse.h sparse_util.h smxsm.cpp
	$(CC) -osmxsm.x smxsm.cpp

smxsv.x : sparse.h sparse_util.h smxsv.cpp
	$(CC) -osmxsv.x smxsv.cpp

m2sm.x : matrix.h matrix_util.h sparse.h sparse_util.h m2sm.cpp
	$(CC) -om2sm.x m2sm.cpp

sm2m.x : matrix.h matrix_util.h sparse.h sparse_util.h sm2m.cpp
	$(CC) -osm2m.x sm2m.cpp

fhtbl.x : hashtbl.h $(tcpp)/hashclasses.h $(cpp)/hashfunctions.h $(cpp)/hashfunctions.cpp \
          $(cpp)/primes.h $(cpp)/primes.cpp fhtbl.cpp
	$(CC) -ofhtbl.x fhtbl.cpp

rantable.x : $(cpp)/xstring.h $(cpp)/xstring.cpp \
             $(cpp)/xran.h $(cpp)/xran.cpp $(cpp)/xranxstr.cpp \
             rantable.cpp
	$(CC) -orantable.x rantable.cpp

