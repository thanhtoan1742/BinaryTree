run: main
	./main

main: main.cpp BSTree.hpp
	g++ main.cpp -o main