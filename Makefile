test: build/test.o build/json_object.o build/json_serializer.o build/json_deserializer.o
	g++ build/test.o -o test build/json_object.o build/json_serializer.o build/json_deserializer.o

build/test.o: src/test.cpp src/lib/json_object.h
	g++ -c src/test.cpp -o build/test.o

build/json_object.o: src/lib/json_object.cpp src/lib/json_object.h
	g++ -c src/lib/json_object.cpp -o build/json_object.o

build/json_serializer.o: src/lib/json_serializer.cpp src/lib/json_serializer.h
	g++ -c src/lib/json_serializer.cpp -o build/json_serializer.o

build/json_deserializer.o: src/lib/json_deserializer.cpp src/lib/json_deserializer.h
	g++ -c src/lib/json_deserializer.cpp -o build/json_deserializer.o