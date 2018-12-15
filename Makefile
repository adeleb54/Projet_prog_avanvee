SRC = Projet.c fonction.c fonction.h structure.c structure.h constante.h
BIN = projet


$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lm -o $(BIN)

clean:
	rm -f $(BIN)