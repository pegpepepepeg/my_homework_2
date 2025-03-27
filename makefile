all:
	g++ -O3 -I. -o tests.o expression.cpp tests.cpp
	g++ -O3 -I. -o differentiator.o expression.cpp differentiator.cpp

test:
	g++ -O3 -I. -o tests.o expression.cpp tests.cpp
	./tests.o
main:
	g++ -O3 -I. -o differentiator.o expression.cpp differentiator.cpp
	./differentiator.o
