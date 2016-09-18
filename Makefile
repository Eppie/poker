all:
	g++ -std=c++14 -g -Ofast -march=native poker.cpp -o poker

clean:
	rm -f poker
