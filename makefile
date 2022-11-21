FLAGS = -g

all: test_Simplex 

test_Simplex: Simplex.o test_Simplex.cpp
	g++ ${FLAGS} Simplex.o test_Simplex.cpp -o test_Simplex

Simplex.o: Simplex.cpp Simplex.h
	g++ -c Simplex.cpp

clear:
	rm -f *.o xsimpl test_Simplex

run_all: all
	./test_Simplex