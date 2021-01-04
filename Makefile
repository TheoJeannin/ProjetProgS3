CC = gcc
CFLAGS = -W -Wall -ansi -pedantic

#Inclure SLD2 et SDL2_image
IFLAGS = -I. -I/usr/include/SDL2/
LIBS = -lSDL2 -lSDL2_image 

#Nom de l'executable :
EXEC = main

#Modifier les sources :
SRC = Base_SDL/src/extensionsdl.c Base_SDL/src/affichage.c Base_SDL/src/logique.c  Base_SDL/src/main.c
OBJ = $(SRC:.c=.o)


all: $(EXEC)

main: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(IFLAGS) $(LIBS) -lm

%.o: %.c
	@$(CC) -o $@ $^ $(LDFLAGS) $(IFLAGS) $(LIBS)-lm

clean:
	@rm -rf *.o
	
mrproper: clean
	@rm -rf 