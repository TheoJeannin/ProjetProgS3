CC = gcc
CFLAGS = -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs  -L./SDL2_image/.libs
LDFLAGS = `sdl2-config --libs --cflags` -lSDL2_image -lm
INCLUDES =  -I./SDL2_ttf  -I./SDL2_image
EXEC = main
SRC = src/extensionsdl.c src/affichage.c src/logique.c src/main.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)
