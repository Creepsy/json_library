cmake_minimum_required(VERSION 3.10)


project(json_library)

set(JSON_LIBRARY_FILES
    src/lib/json_builder.cpp
    src/lib/json_reader.cpp
    src/lib/json.cpp

    src/lib/json_builder.h
    src/lib/json_reader.h
    src/lib/json.h
)

add_executable(test src/test.cpp ${JSON_LIBRARY_FILES})