run: main
	./main

main: main.cpp BSTree.hpp
	g++ -std=c++11 -Wall main.cpp -o main
