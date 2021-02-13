
main: main.o
	g++ main.cpp -o main -lSDL2 -lSDL2_image
	
main.o: main.cpp
	g++ -c main.cpp
	
run:
	./main
	
clean:
	rm *.o main
