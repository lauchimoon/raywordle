CC=gcc
SRC=raywordle.c
LDLIBS=-L/home/lauren/software/raylib/src -lraylib -lm -ldl -lpthread -lGL
INCLUDE=-I/home/lauren/software/raylib/src
OUT=raywordle

default:
	$(CC) -o $(OUT) $(SRC) $(LDLIBS) $(INCLUDE)
