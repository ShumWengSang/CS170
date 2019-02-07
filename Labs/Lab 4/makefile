# Macros ========================================

CC=g++
CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -Wconversion -O

OUTDIR=gnu/
ERASE=rm
OBJECTS=main.o List.o
EXE=lab
PROJECT_NAME=Lab 4 Roland Shum
INPUT_FILE = List.cpp

# Targets ========================================
all : $(EXE)

$(EXE) : $(OBJECTS)
	cd ./$(OUTDIR); \
	$(CC) $(OBJECTS) -o $(EXE)
  
main.o : driver.cpp 
	$(CC) $(CFLAGS) -c driver.cpp -o $(OUTDIR)main.o

List.o : List.cpp 
	$(CC) $(CFLAGS) -c List.cpp -o $(OUTDIR)List.o
	
clean :
	cd ./$(OUTDIR); \
	$(ERASE) $(EXE) $(OBJECTS)
  
CRDoxygen :
	( cat ./Doxyfile ; echo "PROJECT_NAME=$(PROJECT_NAME)" ; echo "INPUT = $(INPUT_FILE)") | doxygen -
  
Diff : 
	$(MAKE) -C $(OUTDIR) Diff
	
Memory :
	drmemory -batch -no_summary -- $(OUTDIR)$(EXE)
	
Run :
	$(MAKE) -C $(OUTDIR) Run