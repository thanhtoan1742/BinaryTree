run: main
	./main

fileout: main
	./main > output.txt

main: main.cpp BSTree.hpp AVLTRee.hpp
	g++ -std=c++11 -Wall main.cpp -o main

clean:
	rm main
