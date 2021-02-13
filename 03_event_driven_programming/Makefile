
main: main.o
	g++ main.o ../src/* -o main -lSDL2
	
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm main *.o

run:
	./main
