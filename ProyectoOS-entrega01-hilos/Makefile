# Makefile De Proyecto01_Sisop

# Banderas y compilador
CC = gcc
CFLAGS = -w -std=c11 -pthread

# nombres de archivos fuentes, headers y ejecutables
SRC = principal.c
HDR = modulo.h
EXE = principal

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)
