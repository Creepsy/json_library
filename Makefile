test: build/test.o build/json_object.o
	g++ build/test.o -o test build/json_object.o

build/test.o: src/test.cpp src/lib/json_object.h
	g++ -c src/test.cpp -o build/test.o

build/json_object.o: src/lib/json_object.cpp src/lib/json_object.h
	g++ -c src/lib/json_object.cpp -o build/json_object.o