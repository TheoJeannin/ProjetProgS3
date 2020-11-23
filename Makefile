CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf
INCLUDES = `sdl2-config --cflags` -lSDL2_ttf
#Nom de l'executable :
EXEC = main
#Modifier les sources :
SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o tests/*.o *~ $(EXEC)
mrproper: clean
	rm -rf $(EXEC)
doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex
push :
	git push https://github.com/TheoJeannin/ProjetProgS3.git
