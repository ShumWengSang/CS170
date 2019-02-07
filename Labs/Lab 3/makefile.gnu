# Macros ========================================

CC=g++
CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -Wconversion -O

OUTDIR=gnu/
ERASE=rm
OBJECTS=fibonacci.o main.o
EXE=game
PROJECT_NAME=Lab 1 Roland Shum
INPUT_FILE = fibonacci.cpp

# Targets ========================================
all : $(EXE)

$(EXE) : $(OBJECTS)
	cd ./$(OUTDIR); \
	$(CC) $(OBJECTS) -o $(EXE)
  
main.o : Main.cpp 
	$(CC) $(CFLAGS) -c Main.cpp -o $(OUTDIR)main.o

fibonacci.o : fibonacci.cpp 
	$(CC) $(CFLAGS) -c fibonacci.cpp -o $(OUTDIR)fibonacci.o
	
clean :
	cd ./$(OUTDIR); \
	$(ERASE) $(EXE) $(OBJECTS)
  
CRDoxygen :
	( cat ./Doxyfile ; echo "PROJECT_NAME=$(PROJECT_NAME)" ; echo "INPUT = $(INPUT_FILE)") | doxygen -
  
Diff : 
	$(MAKE) -C Diff