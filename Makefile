test: build/test.o
	g++ build/test.o -o test

build/test.o : src/test.cpp
	g++ -c src/test.cpp -o build/test.o
