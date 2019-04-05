BIN  = kmeans

CXX=g++
CC=g++
SHELL=/bin/sh

# CPPFLAGS= -L /usr/lib/libp/  -pg
GCPPFLAGS=-g -Wall
CPPFLAGS=-O3 -Wall

CFLAGS=$(CPPFLAGS)
LIBS = -lm

SRCS=\
$(BIN).cpp\
$(BIN)p.cpp\
mat.cpp\
rand.cpp\
randf.cpp\
randmt.cpp

HDRS=\
mat.h\
rand.h

OBJS=\
mat.o\
rand.o

# all: $(BIN)
all: $(BIN) $(BIN)p

$(BIN):	$(OBJS) $(BIN).o
	$(CC) $(CFLAGS) $(OBJS) $(BIN).o $(LIBS) -o $(BIN)

$(BIN)p:	$(OBJS) $(BIN)p.o
	$(CC) $(CFLAGS) $(OBJS) $(BIN).o $(LIBS) -o $(BIN)p

debug$(BIN):	$(OBJS) $(BIN).o
	$(CC) $(GCPPFLAGS) $(OBJS) $(BIN).o $(LIBS) -o $(BIN)

size:	$(HDRS)  $(SRCS) 
	wc -l $?

srcs:	$(HDRS)  $(SRCS) 
	echo $(HDRS)  $(SRCS) 

all:
	touch $(HDRS)  $(SRCS) 

debug:	$(OBJS) $(BIN).cpp
	$(CC) $(GCPPFLAGS) $(OBJS) $(BIN).cpp $(LIBS) -o $(BIN)

clean:
	/bin/rm -f *.o $(BIN)*.tar *~ core gmon.out a.out

tar: makefile $(SRCS) $(HDRS)
	tar -cvf "hw5.tar" $(SRCS) $(HDRS) $(DOCS) makefile
	ls -l $(BIN)*tar