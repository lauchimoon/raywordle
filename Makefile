CC = gcc
SRC = raywordle.c
RAYLIB_PATH ?= /home/lauren/software/raylib
LDLIBS = -L$(RAYLIB_PATH)/src -lraylib -lm -ldl -lpthread -lGL
INCLUDE = -I$(RAYLIB_PATH)/src
OUT = raywordle

default:
	$(CC) -o $(OUT) $(SRC) $(LDLIBS) $(INCLUDE)
