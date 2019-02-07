PRG=gnu.exe
GCC=g++32.bat
GCCFLAGS=-Wall -Wextra -ansi -pedantic -O -Wconversion -Werror -g

OBJECTS0=Ocean.cpp PRNG.cpp
DRIVER0=driver-big.cpp

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines -b

PROJECT_NAME = Assignment 1 Warboat Roland Shum
INPUT_FILE = Ocean.cpp

gcc64:
	g++ -o $(PRG) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
clang64:
	clang++ -o $(PRG) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
0:
	#echo "running test$@"
	#@echo "should run in less than 200 ms"
	@echo "should run in less than 200 ms"
	./$(PRG) input.txt >studentout$@
	#diff output$@.txt studentout$@ $(DIFF_OPTIONS) > difference$@
clean : 
	rm *.exe student* difference*
	
memory : 
	$(GCC) -o $(PRG) $(DRIVER0) $(OBJECTS0) -g $(GCCFLAGS)
	drmemory -batch -no_summary -- $(PRG)
  
CRDoxygen :
	( cat ./Doxyfile ; echo "EXTRACT_ALL=YES" )| doxygen -
	( cat ./Doxyfile ; echo "PROJECT_NAME=$(PROJECT_NAME)" ; echo "INPUT = $(INPUT_FILE)" ; echo "EXTRACT_ALL=NO ") | doxygen -