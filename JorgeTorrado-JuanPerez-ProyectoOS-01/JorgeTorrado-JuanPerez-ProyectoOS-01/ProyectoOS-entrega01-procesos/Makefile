# Makefile for Proyecto01_Sisop

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source file and executable name
SRC = pdispersa.c
HDR = pdispersa.h
EXE = pdispersa

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)

.PHONY: all clean
