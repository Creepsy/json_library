args = -g

test: build/test.o build/json.o build/json_builder.o
	g++ build/test.o -o test build/json.o build/json_builder.o $(args)

build/test.o: src/test.cpp src/lib/json.h src/lib/json_builder.h 
	g++ -c src/test.cpp -o build/test.o $(args)

build/json.o: src/lib/json.cpp src/lib/json.h
	g++ -c src/lib/json.cpp -o build/json.o $(args)

build/json_builder.o: src/lib/json_builder.cpp src/lib/json_builder.h build/json.o
	g++ -c src/lib/json_builder.cpp -o build/json_builder.o $(args)