
main: main.o
	g++ main.o -o main -lSDL2 
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o main

run:
	./main

debug:
	g++ -g main.cpp -lSDL2
	gdb a.out
	rm a.out
