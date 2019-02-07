# Macros ========================================

CC=g++
CFLAGS= -Wall -Wextra -Werror -ansi -pedantic

OUTDIR=gnu/
ERASE=rm
OBJECTS=Parser.o Map.o Inventory.o Command.o main.o
EXE=game

# Targets ========================================
all : $(EXE)

$(EXE) : $(OBJECTS)
	cd ./$(OUTDIR); \
	$(CC) $(OBJECTS) -o $(EXE)
  
main.o : Main.cpp Inventory.h Parser.h Map.h Command.h
	$(CC) $(CFLAGS) -c Main.cpp -o $(OUTDIR)main.o

Parser.o : Parser.cpp Parser.h
	$(CC) $(CFLAGS) -c Parser.cpp -o $(OUTDIR)Parser.o 
  
Map.o : Map.cpp Map.h Inventory.h
	$(CC) $(CFLAGS) -c Map.cpp -o $(OUTDIR)Map.o
  
Inventory.o : Inventory.cpp Inventory.h
	$(CC) $(CFLAGS) -c Inventory.cpp -o $(OUTDIR)Inventory.o
  
Command.o : Command.cpp Command.h
	$(CC) $(CFLAGS) -c Command.cpp -o $(OUTDIR)Command.o
	
clean :
	cd ./$(OUTDIR); \
	$(ERASE) $(EXE) $(OBJECTS)
