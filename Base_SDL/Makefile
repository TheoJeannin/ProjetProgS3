WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = 

INC = -I./include
CFLAGS = -Wall
RESINC = 
LIBDIR = -L./lib
LIB = 
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_image -lSDL2_ttf

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB) 
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/ProjetBase

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB) 
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/ProjetBase

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/affichage.o $(OBJDIR_DEBUG)/src/extensionsdl.o $(OBJDIR_DEBUG)/src/logique.o $(OBJDIR_DEBUG)/src/main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/extensionsdl.o $(OBJDIR_RELEASE)/src/logique.o $(OBJDIR_RELEASE)/src/main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/src/affichage.o: src/affichage.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/affichage.c -o $(OBJDIR_DEBUG)/src/affichage.o

$(OBJDIR_DEBUG)/src/extensionsdl.o: src/extensionsdl.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/extensionsdl.c -o $(OBJDIR_DEBUG)/src/extensionsdl.o

$(OBJDIR_DEBUG)/src/logique.o: src/logique.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/logique.c -o $(OBJDIR_DEBUG)/src/logique.o

$(OBJDIR_DEBUG)/src/main.o: src/main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.c -o $(OBJDIR_DEBUG)/src/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/src/extensionsdl.o: src/extensionsdl.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/extensionsdl.c -o $(OBJDIR_RELEASE)/src/extensionsdl.o

$(OBJDIR_RELEASE)/src/logique.o: src/logique.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/logique.c -o $(OBJDIR_RELEASE)/src/logique.o

$(OBJDIR_RELEASE)/src/main.o: src/main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.c -o $(OBJDIR_RELEASE)/src/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

