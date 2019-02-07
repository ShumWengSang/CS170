# Macros ========================================

CC=g++
CFLAGS= -Wall -Wextra -Werror -ansi -pedantic

ERASE=rm
OBJECTS=hw-gnu.o
EXE=hw-gnu

# Targets ========================================
all : $(EXE)

$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXE)

hw-gnu.o : hw.cpp
	$(CC) $(CFLAGS) -c hw.cpp -o hw-gnu.o 
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)
