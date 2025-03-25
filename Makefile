# Définition des variables
CC = gcc
CFLAGS = -Iinclude $(shell sdl2-config --cflags)  # Options pour compiler les fichiers .c
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image  # Options pour l'édition des liens

SRC = src/SDL_VSYNC.c src/maSDL.c src/types.c src/listeDouble.c src/ligneBus.c src/main.c  # Tous les fichiers source
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))  # Transforme chaque .c en .o dans obj/
BIN = bin/main  # Nom de l'exécutable

# Cible principale : Compiler tout
all: $(BIN)

# Compilation de l'exécutable
$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

# Compilation des fichiers .c en .o
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -rf obj/*.o bin/main

# Recompile proprement
rebuild: clean all

# Exécution du programme
run: $(BIN)
	./$(BIN)