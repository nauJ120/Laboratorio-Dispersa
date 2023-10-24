# Makefile para el proyecto en hilos

# banderas
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread

# archivo fuente y ejecutable
SRC = hdispersa.c
HDR = hdispersa.h
EXE = hdispersa

all: $(EXE)

$(EXE): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)

.PHONY: all clean

