CC=g++
CFLAGS=-std=c++11 -O3 -Wall

OBJECTS=src/main.o src/config.o src/instance.o src/solution.o src/rules/initial_solution.o src/rules/choice.o src/rules/neighbourhood.o src/rules/cost.o src/rules/IterativeImprovement.o src/rules/Vnd.o src/rules/SimulatedAnnealing.o src/rules/IterativeLocalSearch.o

.PHONY: clean

all: lop

lop: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o lop

statistics: lop
	./statistics.sh

clean:
	rm -f src/*~ src/*.o src/rules/*.o statistics/*/*.txt lop
