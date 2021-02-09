test: build/test.o build/json.o
	g++ build/test.o -o test build/json.o 

build/test.o: src/test.cpp src/lib/json.h
	g++ -c src/test.cpp -o build/test.o

build/json.o: src/lib/json.cpp src/lib/json.h
	g++ -c src/lib/json.cpp -o build/json.o